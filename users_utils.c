// Copyright 2022 Rares Matei Dumitrescu mateidum828@gmail.com

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "structures.h"
#include "hashtable_utils.h"

#define U_MAX 20

void add_user(hashtable_t *users_ht, char user_name[U_MAX]) {
    if (ht_has_key(users_ht, user_name)) {
        printf("User is already registered.\n");
        return;
    }
    int user_name_size = strlen(user_name);
    user_info_t user_info;
    user_info.points = 0;
    user_info.banned = 0;
    ht_put(users_ht, user_name, user_name_size, NULL, 0, &user_info);
}