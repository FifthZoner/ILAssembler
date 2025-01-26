#include "translator.h"

#include <iso646.h>
#include <stdlib.h>

// this might be used for jump label resolution too

void translator_add(Translator* translator,
                                const char* key, uint32_t key_length, TranslatorEntry descriptor, uint32_t index) {

    if (key_length == 0) {
        return;
    }

    if (key_length == index) {
        translator->descriptor = descriptor;
        return;
    }

    if (translator->next_level_size == 0) {
        translator->next_level_size = 1;
        translator->next_level = (Translator*)malloc(sizeof(Translator));
        translator->next_level[0].key_letter = key[index];
        translator->next_level[0].next_level_size = 0;
        translator->next_level[0].next_level = nullptr;
        return translator_add(&translator->next_level[0], key, key_length, descriptor, index + 1);
    }

    // search for the letter to see if it exists
    for (uint32_t current = translator->next_level_size / 2, bound_lower = 0, bound_upper = translator->next_level_size - 1;;) {
        // if the next letter was found do a recursive call to find the next node
        if (translator->next_level[current].key_letter == key[index]) {
            return translator_add(&translator->next_level[current], key, key_length, descriptor, index + 1);
        }

        // at this point if bounds are the same then there is no way for this key to work
        if (bound_lower == bound_upper) {
            translator->next_level_size++;
            Translator* new_next_level = (Translator*)malloc(sizeof(Translator) * translator->next_level_size);
            if (translator->next_level[current].key_letter > key[index]) {
                // in that case the new entry needs to be put at the current index
                for (uint32_t n = 0; n < current; n++) {
                    new_next_level[n] = translator->next_level[n];
                }
                new_next_level[current].key_letter = key[index];
                new_next_level[current].next_level_size = 0;
                new_next_level[current].next_level = nullptr;
                for (uint32_t n = current; n < translator->next_level_size - 1; n++) {
                    new_next_level[n + 1] = translator->next_level[n];
                }

                free(translator->next_level);
                translator->next_level = new_next_level;
                return translator_add(&translator->next_level[current], key, key_length, descriptor, index + 1);
            }
            else {
                // in that case the new entry needs to be put after the current index
                for (uint32_t n = 0; n <= current; n++) {
                    new_next_level[n] = translator->next_level[n];
                }
                new_next_level[current + 1].key_letter = key[index];
                new_next_level[current + 1].next_level_size = 0;
                new_next_level[current + 1].next_level = nullptr;
                for (uint32_t n = current + 1; n < translator->next_level_size - 1; n++) {
                    new_next_level[n + 1] = translator->next_level[n];
                }

                free(translator->next_level);
                translator->next_level = new_next_level;
                return translator_add(&translator->next_level[current + 1], key, key_length, descriptor, index + 1);
            }
        }

        // if the letter in array is larger than the searched one reduce the current index
        if (translator->next_level[current].key_letter > key[index]) {
            bound_upper = current;
            current = (bound_lower + bound_upper) / 2;
        }
        // do the reverse otherwise
        else {
            bound_lower = current + 1;
            if (bound_lower > bound_upper) {
                bound_lower = bound_upper;
            }
            current = (bound_lower + bound_upper) / 2;
        }
    }

    // all cases should be covered
}

const TranslatorEntry* translator_get(Translator* translator,
                                const char* key, uint32_t key_length, uint32_t index) {

    // to avoid the situation where the translator structure is empty or key is empty
    if (index == 0 and (translator->next_level_size == 0 or key_length == 0)) {
        return nullptr;
    }

    // if the last index was reached return the descriptor at given level
    if (index == key_length) {
        // if key is NULL character then this is not a valid path, return error value
        if (translator->key_letter == 0) {
            return nullptr;
        }
        return &translator->descriptor;
    }

    // if the code reached this place a search is needed to find the next node
    for (uint32_t current = translator->next_level_size / 2, bound_lower = 0, bound_upper = translator->next_level_size - 1;;) {
        // if the next letter was found do a recursive search for the next
        if (translator->next_level[current].key_letter == key[index]) {
            return translator_get(&translator->next_level[current], key, key_length, index + 1);
        }

        // at this point if bounds are the same then there is no way for this key to work
        if (bound_lower == bound_upper) {
            return nullptr;
        }

        // if the letter in array is larger than the searched one reduce the current index
        if (translator->next_level[current].key_letter > key[index]) {
            bound_upper = current - 1;
            current = (bound_lower + bound_upper) / 2;
        }
        // do the reverse otherwise
        else {
            bound_lower = current + 1;
            if (bound_lower > bound_upper) {
                bound_lower = bound_upper;
            }
            current = (bound_lower + bound_upper) / 2;
        }
    }

    return nullptr;
}

void translator_clear (const Translator* translator) {
    for (uint32_t n = 0; n < translator->next_level_size; n++) {
        translator_clear(&translator->next_level[n]);
    }
    if (translator->next_level_size != 0) {
        free(translator->next_level);
    }
    if (translator->descriptor.content.jump_address != 0) {
        // there is something in the descriptor
        if (translator->descriptor.is_variable) {
            for (uint64_t n = 0; n < translator->descriptor.content.variable->token_amount; n++) {
                free_lexer_token(translator->descriptor.content.variable->tokens + n);
            }
        }
        // in case of jump labels and functions there is no need to deallocate
    }
}