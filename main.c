/********* main.c ********
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a3_nodes.h"
#include "a3_functions.h"
#include <ctype.h>

int main()
{
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }

    user_t *users = read_CSV_and_create_users(csv_file, 50);
    fclose(csv_file);

    printf("**** Welcome to Text-Based Facebook ****\n");

    int choice = 0;

    while (1)
    {
        print_menu();
        scanf("%d", &choice);

        if (choice < 1 || choice > 6)
        {
            printf("Invalid choice. Please try again.\n");
            continue;
        }

        if (choice == 1)
        {
            char username[30];
            char password[15];

            printf("Enter a username: ");
            scanf("%s", username);

            for (int i = 0; username[i]; i++)
                username[i] = tolower(username[i]);

            if (find_user(users, username) != NULL)
            {
                printf("User already exists!\n");
                continue;
            }

            do {
                printf("Enter an up to 15 characters password: ");
                scanf("%s", password);

                if (strlen(password) < 8)
                    printf("Password too short! Please enter at least 8 characters.\n");
            } while (strlen(password) < 8);

            users = add_user(users, username, password);
            printf("**** User Added! ****\n");
        }

        else if (choice == 2)
        {
            char username[30];
            char old_pass[15];
            char new_pass[15];

            printf("Enter a username to update their password: ");
            scanf("%s", username);

            for (int i = 0; username[i]; i++)
                username[i] = tolower(username[i]);

            user_t *user_ptr = find_user(users, username);
            if (user_ptr == NULL)
            {
                printf("Error: User not found!\n");
                continue;
            }

            printf("Enter the password: ");
            scanf("%s", old_pass);

            if (strcmp(old_pass, user_ptr->password) != 0)
            {
                printf("Password incorrect.\n");
                continue;
            }

            do {
                printf("Enter a new password, up to 15 characters: ");
                scanf("%s", new_pass);

                if (strlen(new_pass) < 8)
                    printf("Password too short! Must be at least 8 characters.\n");
            } while (strlen(new_pass) < 8);

            strcpy(user_ptr->password, new_pass);
            printf("**** Password changed! ****\n");
        }

        else if (choice == 3)
        {
            char username[30];

            printf("Enter a username to manage their posts: ");
            scanf("%s", username);

            for (int i = 0; username[i]; i++)
                username[i] = tolower(username[i]);

            user_t *user_ptr = find_user(users, username);
            if (user_ptr == NULL)
            {
                printf("Error: User not found!\n");
                continue;
            }

            int post_choice = 0;

            while (1)
            {
                printf("-----------------------------------------------------------------------\n");
                printf("Managing %s’s posts\n", user_ptr->username);
                printf("-----------------------------------------------------------------------\n");

                if (user_ptr->posts == NULL)
                    printf("Note: No posts available for %s\n", user_ptr->username);

                printf("1. Add a new post\n");
                printf("2. Remove a post\n");
                printf("3. Return to main menu\n");
                printf("Enter your choice: ");

                scanf("%d", &post_choice);

                if (post_choice == 1)
                {
                    char text[250];
                    printf("Enter your post content: ");
                    scanf(" %[^\n]s", text);

                    add_post(user_ptr, text);
                    display_all_user_posts(user_ptr);
                }
                else if (post_choice == 2)
                {
                    if (!delete_post(user_ptr))
                        printf("No posts to delete.\n");
                    else
                    {
                        printf("Post removed.\n");
                        display_all_user_posts(user_ptr);
                    }
                }
                else if (post_choice == 3)
                    break;
            }
        }

        else if (choice == 4)
        {
            char username[30];

            printf("Enter a username to update their friends: ");
            scanf("%s", username);

            for (int i = 0; username[i]; i++)
                username[i] = tolower(username[i]);

            user_t *user_ptr = find_user(users, username);
            if (user_ptr == NULL)
            {
                printf("Error: User not found!\n");
                continue;
            }

            int friend_choice = 0;

            while (1)
            {
                printf("-----------------------------------------------------------------------\n");
                printf("Managing %s’s friends\n", user_ptr->username);
                printf("-----------------------------------------------------------------------\n");

                printf("1. Add a new friend\n");
                printf("2. Remove a friend\n");
                printf("3. Return to main menu\n");
                printf("Enter your choice: ");

                scanf("%d", &friend_choice);

                if (friend_choice == 1)
                {
                    char fname[30];
                    printf("Enter a new friend's name: ");
                    scanf("%s", fname);

                    for (int i = 0; fname[i]; i++)
                        fname[i] = tolower(fname[i]);

                    add_friend(user_ptr, fname);
                    printf("Friend added to the list.\n");
                }

                else if (friend_choice == 2)
                {
                    display_user_friends(user_ptr);

                    char fname[30];
                    printf("Enter a friend’s name to delete: ");
                    scanf("%s", fname);

                    for (int i = 0; fname[i]; i++)
                        fname[i] = tolower(fname[i]);

                    if (delete_friend(user_ptr, fname))
                        display_user_friends(user_ptr);
                    else
                        printf("Invalid friend name.\n");
                }

                else if (friend_choice == 3)
                    break;
            }
        }

        else if (choice == 5)
        {
            char username[30];
            printf("Enter a username to display their posts: ");
            scanf("%s", username);

            for (int i = 0; username[i]; i++)
                username[i] = tolower(username[i]);

            user_t *user_ptr = find_user(users, username);
            if (user_ptr == NULL)
            {
                printf("Error: User not found!\n");
                continue;
            }
            display_all_user_posts(user_ptr);
        }
        else if (choice == 6)
        {
            printf("Goodbye!\n");
            teardown(users);
            return 0;
        }
    }
}
