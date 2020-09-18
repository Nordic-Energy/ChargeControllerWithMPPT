/********************************************************************************
 * class        Recursive array sorting                                         *
 *                                                                              *
 * file         FastSort.h                                                      *
 * author       @RedCommissary                                                  *
 * date         01.07.2020                                                      *
 *                                                                              *
 ********************************************************************************/

#pragma once

/********************************************************************************
 * Class array sorting
 ********************************************************************************/

class FastSort {
    public:
        static void Recursive (uint16_t *array, uint16_t size) {
            int i = 0;
            int j = size - 1;

            uint16_t mid = array[size / 2];

            do {
                while(array[i] < mid) {
                    i++;
                }

                while(array[j] > mid) {
                    j--;
                }

                if (i <= j) {
                    uint16_t tmp = array[i];
                    array[i] = array[j];
                    array[j] = tmp;

                    i++;
                    j--;
                }
            } while (i <= j);

            if (j > 0) { Recursive(array, j + 1); }
            if (i < size) { Recursive(&array[i], size - i); }
        }
};