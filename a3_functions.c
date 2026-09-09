#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>
#include "a3_nodes.h"
#include "a3_functions.h"
#include <ctype.h>

//menu display
void print_menu()
{
    printf("***********************************************\n");
    printf("MAIN MENU:\n");
    printf("***********************************************\n");
    printf("1. Register a new user\n");
    printf("2. Manage a user's profile (change password)\n");
    printf("3. Manage a user's posts (add/remove)\n");
    printf("4. Manage a user's friends (add/remove)\n");
    printf("5. Display a user’s posts\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}
//teardown
void teardown(user_t *users)
{
    while (users != NULL)
    {
        post_t *p = users->posts;
        while (p != NULL)
        {
            post_t *temp = p;
            p = p->next;
            free(temp);
        }
        friend_t *f = users->friends;
        while (f != NULL)
        {
            friend_t *temp = f;
            f = f->next;
            free(temp);
        }
        user_t *temp = users;
        users = users->next;
        free(temp);
    }
}

//find user
user_t *find_user(user_t *users, const char *username)
{
    while (users != NULL)
    {
        if (strcmp(users->username, username) == 0)
            return users;
        users = users->next;
    }
    return NULL;
}

//add user
user_t *add_user(user_t *users, const char *username, const char *password)
{
    //lowercase
    char lower_username[30];
    int i;
    for (i = 0; username[i] != '\0'; i++) {
        lower_username[i] = tolower(username[i]);
    }
    lower_username[i] = '\0';

    //check duplicate user
    user_t *curr = users;
    while (curr != NULL) {
        if (strcmp(curr->username, lower_username) == 0) {
            return users;
        }
        curr = curr->next;
    }

    //new user
    user_t *new_user = malloc(sizeof(user_t));
    strcpy(new_user->username, lower_username);
    strcpy(new_user->password, password);
    new_user->friends = NULL;
    new_user->posts = NULL;
    new_user->next = NULL;

    //alphabetically into linked list
    if (users == NULL || strcmp(lower_username, users->username) < 0) {
        new_user->next = users;
        return new_user;
    }
    curr = users;
    while (curr->next != NULL &&
           strcmp(curr->next->username, lower_username) < 0) {
        curr = curr->next;
    }
    new_user->next = curr->next;
    curr->next = new_user;
    return users;
}
//create friend
friend_t *create_friend(const char *username)
{
    friend_t *new_friend = malloc(sizeof(friend_t));
    if (!new_friend) {
        return NULL;
    }
    strcpy(new_friend->username, username);
    new_friend->next = NULL;
    return new_friend;
}
//add friend
void add_friend(user_t *user, const char *friend_name)
{
    if (user == NULL) return;
    friend_t *new_friend = create_friend(friend_name);
    if (new_friend == NULL) return;
    //no friends or insert at front
    if (user->friends == NULL || 
        strcmp(friend_name, user->friends->username) < 0)
    {
        new_friend->next = user->friends;
        user->friends = new_friend;
        return;
    }
    //insert middle or end
    friend_t *curr = user->friends;
    while (curr->next != NULL &&
           strcmp(curr->next->username, friend_name) < 0)
    {
        curr = curr->next;
    }
    new_friend->next = curr->next;
    curr->next = new_friend;
}
//create post
post_t *create_post(const char *text)
{
    post_t *new_post = malloc(sizeof(post_t));
    if (!new_post) return NULL;

    strcpy(new_post->content, text);
    new_post->next = NULL;

    return new_post;
}
//add post
void add_post(user_t *user, const char *text)
{
    if (user == NULL) return;
    post_t *new_post = create_post(text);
    new_post->next = user->posts;
    user->posts = new_post;
}
//delete post
_Bool delete_post(user_t *user)
{
    if (user == NULL || user->posts == NULL)
        return false;
    post_t *temp = user->posts;
    user->posts = user->posts->next;
    free(temp);
    return true;
}
//display all posts
void display_all_user_posts(user_t *user)
{
    if (user == NULL) return;
    post_t *curr = user->posts;
    if (curr == NULL) {
        printf("No posts available for %s.\n", user->username);
        return;
    }
    printf("-----------------------------------------------------------------------\n");
    printf("%s's posts\n", user->username);
    int index = 1;
    while (curr != NULL) {
        printf("%d - %s\n", index, curr->content);
        curr = curr->next;
        index++;
    }
    printf("-----------------------------------------------------------------------\n");
}
//display only some posts
void display_posts_by_n(user_t *user, int number)
{
    if (user == NULL) return;
    post_t *curr = user->posts;
    if (curr == NULL) {
        printf("No posts available for %s.\n", user->username);
        return;
    }
    char choice;
    int count = 0;
    while (curr != NULL)
    {
        printf("%d - %s\n", count + 1, curr->content);
        curr = curr->next;
        count++;
        if (count % number == 0)
        {
            printf("Do you want to display more posts? (Y/N): ");
            scanf(" %c", &choice);

            if (choice == 'N' || choice == 'n')
                return;
        }
    }
    printf("All posts have been displayed.\n");
}
//display friends
void display_user_friends(user_t *user)
{
    if (user == NULL) return;
    friend_t *curr = user->friends;
    if (curr == NULL) {
        printf("No friends available for %s.\n", user->username);
        return;
    }
    printf("List of %s’s friends:\n", user->username);
    int index = 1;
    while (curr != NULL) {
        printf("%d - %s\n", index, curr->username);
        curr = curr->next;
        index++;
    }
}

//delete friend
_Bool delete_friend(user_t *user, char *friend_name)
{
    if (user == NULL || user->friends == NULL)
        return false;
    friend_t *curr = user->friends;
    //friend is at head
    if (strcmp(curr->username, friend_name) == 0)
    {
        user->friends = curr->next;
        free(curr);
        return true;
    }
    //search in list
    friend_t *prev = curr;
    curr = curr->next;
    while (curr != NULL)
    {
        if (strcmp(curr->username, friend_name) == 0)
        {
            prev->next = curr->next;
            free(curr);
            return true;
        }
        prev = curr;
        curr = curr->next;
    }
    return false; 
}

/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and should be used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
    srand(time(NULL));
    user_t *users = NULL;
    char buffer[500];
    fgets(buffer, sizeof(buffer), file); // Read and discard the header line
    int count = 0;
    for (int i = 0; i < num_users; i++)
    {
        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

        char *token = strtok(buffer, ",");
        char *token2 = strtok(NULL, ",");
        users = add_user(users, token, token2);
        char *username = token;

        token = strtok(NULL, ",");

        user_t *current_user = users;
        for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
            ;

        while (token != NULL && strcmp(token, ",") != 0 && count < 3)
        {
            if (strcmp(token, " ") != 0)
            {
                add_friend(current_user, token);
            }
            token = strtok(NULL, ",");
            count++;
        }
        count = 0;

        // token = strtok(NULL, ",");
        while (token != NULL && strcmp(token, ",") != 0)
        {
            add_post(current_user, token);
            token = strtok(NULL, ",");
        }
    }
    return users;
}
