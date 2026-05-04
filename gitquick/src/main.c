/**!
 * gitquick - A simple git commit helper in C
 * 
 * We can use it like this:
 * 
 * gitquick "feat: add login"
 * gitquick "fix bug" --no-push
 * gitquick "update commit" --amend
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

int is_git_repo() {
    char path[4096];

    if (getcwd(path, sizeof(path)) == NULL) {
        return 0;
    }

    while (1) {
        char git_path[4096];
        snprintf(git_path, sizeof(git_path), "%s/.git", path);

        if (access(git_path, F_OK) == 0) {
            return 1;
        }

        // Si on est à la racine
        if (strcmp(path, "/") == 0) {
            break;
        }

        // Remonter d’un dossier
        char *slash = strrchr(path, '/');
        if (slash) {
            *slash = '\0';
        } else {
            break;
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {

    if (!is_git_repo()) {
        printf("❌ Not a git repository\n");
        return 1;
    }

    if (argc < 2) {
        printf("Usage: gitquick \"commit message\" [--no-push] [--amend]\n");
        return 1;
    }

    char command[1024];
    char message[512] = "";

    int no_push = 0;
    int amend = 0;

    // 🔍 Parse arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--no-push") == 0) {
            no_push = 1;
        } else if (strcmp(argv[i], "--amend") == 0) {
            amend = 1;
        } else {
            strcat(message, argv[i]);
            if (i < argc - 1) strcat(message, " ");
        }
    }

    if (strlen(message) == 0) {
        printf("❌ Commit message is empty\n");
        return 1;
    }

    printf("📦 Adding changes...\n");
    if (system("git add .") != 0) {
        printf("❌ git add failed\n");
        return 1;
    }

    printf("📝 Committing...\n");

    if (amend) {
        snprintf(command, sizeof(command),
                 "git commit --amend -m \"%s\"", message);
    } else {
        snprintf(command, sizeof(command),
                 "git commit -m \"%s\"", message);
    }

    if (system(command) != 0) {
        printf("❌ git commit failed\n");
        return 1;
    }

    if (!no_push) {
        printf("🚀 Pushing...\n");
        if (system("git push") != 0) {
            printf("❌ git push failed\n");
            return 1;
        }
    } else {
        printf("⏭️ Skipping push (--no-push)\n");
    }

    printf("✅ Done!\n");

    return 0;
}