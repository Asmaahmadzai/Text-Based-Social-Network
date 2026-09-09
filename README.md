# Text-Based Social Network
A command-line social networking application written in C. The project demonstrates core data structures and systems programming concepts, including linked lists, dynamic memory allocation, file I/O, string manipulation, and modular program design.

## Features
- Register new users with username and password validation
- Store users alphabetically by username
- Change an existing user's password
- Add and remove friends
- Maintain friend lists in alphabetical order
- Create and remove posts
- Store posts using stack-like behavior
- Display a user's posts
- Display posts incrementally
- Load initial user data from a CSV file
- Dynamically allocate and free users, friends, and posts
- Interactive command-line menu

## Project Structure
| File | Description |
|------|-------------|
| `main.c` | Entry point and command-line menu logic |
| `a3_functions.c` | Implementation of user, friend, post, display, and memory-management functions |
| `a3_functions.h` | Function declarations used throughout the application |
| `a3_nodes.h` | Data structure definitions for users, friends, and posts |
| `user_details.csv` | Initial user data loaded when the application starts |
| `CMakeLists.txt` | CMake configuration for building the project |

## Data Structures
The application uses dynamically allocated linked data structures to represent the social network.

### Users
Users are maintained in a linked list and stored alphabetically by username. Each user contains their account information and references to their friends and posts.

### Friends
Each user maintains a linked list of friends. New friends are inserted in alphabetical order.

### Posts
Each user maintains a linked list of posts using stack-like behavior. New posts are inserted at the beginning of the list, allowing the most recent post to be removed first.

## Core Functions
The project includes functions for:
- Creating and finding users
- Adding users in sorted order
- Creating, adding, and deleting friends
- Creating, adding, and deleting posts
- Displaying user posts and friend lists
- Displaying posts incrementally
- Reading user information from a CSV file
- Releasing dynamically allocated memory before program termination

Example Menu
***********************************************
MAIN MENU:
***********************************************
1. Register a new user
2. Manage a user's profile (change password)
3. Manage a user's posts (add/remove)
4. Manage a user's friends (add/remove)
5. Display a user's posts
6. Exit
Enter your choice:

