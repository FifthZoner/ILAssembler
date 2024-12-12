#include "instruction_translator.h"

#include <iso646.h>
#include <stdlib.h>

// TODO: do a check to see if the descriptor actually exists

void instruction_translator_add(InstructionTranslator* translator,
                                const char* key, uint32_t key_length, InstructionDescriptor descriptor, uint32_t index) {

    if (key_length == 0) {
        return;
    }

    if (key_length == index) {
        translator->descriptor = descriptor;
        return;
    }

    if (translator->next_level_size == 0) {
        translator->next_level_size = 1;
        translator->next_level = (InstructionTranslator*)malloc(sizeof(InstructionTranslator));
        translator->next_level[0].key_letter = key[index];
        return instruction_translator_add(&translator->next_level[0], key, key_length, descriptor, index + 1);
    }

    // search for the letter to see if it exists
    for (uint32_t current = translator->next_level_size / 2, bound_lower = 0, bound_upper = translator->next_level_size - 1;;) {
        // if the next letter was found do a recursive call to find the next node
        if (translator->next_level[current].key_letter == key[index]) {
            return instruction_translator_add(&translator->next_level[current], key, key_length, descriptor, index + 1);
        }

        // at this point if bounds are the same then there is no way for this key to work
        if (bound_lower == bound_upper) {
            // there are multiple elements and there needs to be a reallocation and sorting
            translator->next_level_size++;
            // TODO: address Clion's concern about buffer leak after failed realloc
            translator->next_level = (InstructionTranslator*)realloc(translator->next_level, sizeof(InstructionTranslator) * translator->next_level_size);
            translator->next_level[translator->next_level_size - 1].key_letter = key[index];

            // now move all elements after the current position
            for (uint32_t n = translator->next_level_size - 1; n > current; n--) {
                translator->next_level[n] = translator->next_level[n - 1];
            }

            // and finally populate the given element
            return instruction_translator_add(&translator->next_level[current], key, key_length, descriptor, index + 1);
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

    // all cases should be covered
}

const InstructionDescriptor* instruction_translator_get(InstructionTranslator* translator,
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
            return instruction_translator_get(&translator->next_level[current], key, key_length, index + 1);
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

void instruction_translator_clear (const InstructionTranslator* translator) {
    for (uint32_t n = 0; n < translator->next_level_size; n++) {
        instruction_translator_clear(&translator->next_level[n]);
    }
    if (translator->next_level_size != 0) {
        free(translator->next_level);
    }
}