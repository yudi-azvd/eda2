#include <stdio.h>
#include <string.h>

void clear_buffer() {
  char c;
  while ((c = getchar()) != '\n' && c != EOF) { }
}

#define INITIAL_USERS_CAPACITY 101

int hash(int key, int capacity) {
  return key % capacity;
}

typedef struct user_t {
  int id;
  char first_name[20];
  char second_name[20];
  char birthdate[20];
  char phone_number[20];
} user_t;


void reset_users(user_t* users, int capacity) {
  int i = 0;
  for (; i < capacity; i++) {
    users[i].id = -1;
    users[i].first_name[0] = '\0';
    users[i].second_name[0] = '\0';
    users[i].birthdate[0] = '\0';
    users[i].phone_number[0] = '\0';
  }
}

void insert_user(user_t* users, user_t u) {

}

void del_user(user_t* users, int id) {
  
}

void info_user(user_t* users, int id) {
  
}

void info_user(user_t u) {
  printf("%s %s %s %s", u.first_name, u.second_name, u.birthdate, u.phone_number);
}

void read_user(user_t* u) {
  scanf("%d %s %s %s %s",
    &u->id, u->first_name, u->second_name, u->birthdate, u->phone_number);
}

int main() {
  char command[7];
  int users_capacity = INITIAL_USERS_CAPACITY, user_id;
  user_t user, users[users_capacity];

  while (scanf("%s", command) != EOF) {
    printf("%s\n", command);
    clear_buffer();

    if (strcmp(command, "add") == 0) {
      read_user(&user);
      insert_user(users, user);
    }
    else if (strcmp(command, "del")) {
      scanf("%d", &user_id);
      del_user(users, user_id);
    }
    else if (strcmp(command, "info")) {
      scanf("%d", &user_id);
      info_user(users, user_id);
    }
    else { // commando = "query"

    }
  }
  
  return 0;
}