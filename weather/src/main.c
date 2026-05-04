#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>
#include <time.h>

struct memory {
    char *response;
    size_t size;
};

size_t write_callback(void *data, size_t size, size_t nmemb, void *clientp) {
    size_t total_size = size * nmemb;
    struct memory *mem = (struct memory *)clientp;

    char *ptr = realloc(mem->response, mem->size + total_size + 1);
    if(ptr == NULL) return 0;

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, total_size);
    mem->size += total_size;
    mem->response[mem->size] = 0;

    return total_size;
}

void print_date() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("📅 Date : %02d-%02d-%d\n",
           tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

int main(int argc, char *argv[]) {

    char url[256];

    if (argc > 1 && strcmp(argv[1], "--help") == 0) {
        printf("Usage: weather [city] [--json]\n");
        return 0;
    }

    if (argc > 1 && argv[1][0] != '-') {
        snprintf(url, sizeof(url),
                 "https://wttr.in/%s?format=j1", argv[1]);
    } else {
        snprintf(url, sizeof(url),
                 "https://wttr.in/?format=j1");
    }

    CURL *curl;
    CURLcode res;

    struct memory chunk;
    chunk.response = malloc(1);
    chunk.size = 0;

    curl = curl_easy_init();

    if (!curl) {
        printf("Erreur curl init\n");
        return 1;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    res = curl_easy_perform(curl);

    if (res != CURLE_OK) {
        printf("Erreur curl\n");
        return 1;
    }

    // 📦 JSON parsing
    struct json_object *parsed_json;
    parsed_json = json_tokener_parse(chunk.response);

    struct json_object *current_condition;
    current_condition = json_object_array_get_idx(
        json_object_object_get(parsed_json, "current_condition"), 0);

    struct json_object *temp, *weather_desc;

    json_object_object_get_ex(current_condition, "temp_C", &temp);
    json_object_object_get_ex(current_condition, "weatherDesc", &weather_desc);

    struct json_object *desc0 = json_object_array_get_idx(weather_desc, 0);
    struct json_object *value;

    json_object_object_get_ex(desc0, "value", &value);

    print_date();

    if (argc > 1 && strcmp(argv[1], "--json") == 0) {
        printf("%s\n", chunk.response);
    } else {
        printf("🌤️  Meteo : %s°C, %s\n",
               json_object_get_string(temp),
               json_object_get_string(value));
    }

    // cleanup
    curl_easy_cleanup(curl);
    free(chunk.response);

    return 0;
}