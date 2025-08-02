#ifndef SORT_H
#define SORT_H

#include "Methods.h"

/**
 * @brief Función que ordena un vector de elementos utilizando el algoritmo de selección
 * @param seq Vector de elementos
 * @param size Tamaño del vector
 * @param trace Indica si se debe imprimir el vector en cada paso
 */
template <class Key>
void selectionSort(StaticSequence<Key>& seq, int size, bool trace) {
  for (int i = 0; i < size - 1; i++) {
    int min_index = i;
    for (int j = i + 1; j < size; j++) {
      if (seq[j] < seq[min_index]) {
        min_index = j;
      }
    }

    if (min_index != i) {
      Key temp = seq[i];
      seq[i] = seq[min_index];
      seq[min_index] = temp;
    }
    if (trace) seq.Print();
  }
}


/** ---------------------------------------------------------------------------------------------------
 * @brief Función que particiona un vector de elementos en dos subvectores
 * @param seq Vector de elementos
 * @param low Índice del primer elemento
 * @param high Índice del último elemento
 */
template <class Key>
int partition(StaticSequence<Key>& seq, int low, int high) {
  // std::swap me permite intercambiar el valor de dos elementos de manera eficiente y segura.
  Key pivot = seq[high];
  int i = (low - 1);

  for (int j = low; j <= high - 1; j++) {
    if (seq[j] < pivot) {
      i++;
      std::swap(seq[i], seq[j]);
    }
  }
  std::swap(seq[i + 1], seq[high]);
  return (i + 1);
}

/**
 * @brief Función que sirve de apoyo para el algoritmo de quicksort
 * @param seq Vector de elementos
 * @param low Índice del primer elemento
 * @param high Índice del último elemento
 * @param trace Indica si se debe imprimir el vector en cada paso
 */
template <class Key>
void quickSortHelper(StaticSequence<Key>& seq, int low, int high, bool trace) {
  if (low < high) {
    int pi = partition(seq, low, high);

    quickSortHelper(seq, low, pi - 1, trace);
    quickSortHelper(seq, pi + 1, high, trace);
  }
  if (trace) seq.Print();
}

/**
 * @brief Función que ordena un vector de elementos utilizando el algoritmo de quicksort
 * @param seq Vector de elementos
 * @param size Tamaño del vector
 * @param trace Indica si se debe imprimir el vector en cada paso
 */
template <class Key>
void quickSort(StaticSequence<Key>& seq, int size, bool trace) {
  quickSortHelper(seq, 0, size - 1, trace);
}

/** ---------------------------------------------------------------------------------------------------
 * @brief Función heapify que mantiene la propiedad de un heap
 * @param seq Vector de elementos
 * @param size Tamaño del vector
 * @param i Índice del nodo raíz
 * @param trace Indica si se debe imprimir el vector en cada paso
*/
template <class Key>
void heapify(StaticSequence<Key>& seq, int size, int i, bool trace) {
  int largest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < size && seq[left] > seq[largest]) {
    largest = left;
  }

  if (right < size && seq[right] > seq[largest]) {
    largest = right;
  }

  if (largest != i) {
    std::swap(seq[i], seq[largest]);
    heapify(seq, size, largest, trace);
  }
  if (trace) seq.Print();
}


/**
 * @brief Función que ordena un vector de elementos utilizando el algoritmo de heapsort
 * @param seq Vector de elementos
 * @param size Tamaño del vector
 * @param trace Indica si se debe imprimir el vector en cada paso
 */
template <class Key>
void heapSort(StaticSequence<Key>& seq, int size, bool trace) {
  for (int i = size / 2 - 1; i >= 0; i--) {
    heapify(seq, size, i, trace);
  }

  for (int i = size - 1; i >= 0; i--) {
    std::swap(seq[0], seq[i]);
    heapify(seq, i, 0, trace);
  }
}


/** ---------------------------------------------------------------------------------------------------
 * @brief Función que ordena un vector de elementos utilizando el algoritmo de shellsort
 * @param seq Vector de elementos
 * @param size Tamaño del vector
 * @param trace Indica si se debe imprimir el vector en cada paso
*/
template <class Key>
void shellSort(StaticSequence<Key>& seq, int size, bool trace) {
  float alfa;
  std::cout << "Introduzca el valor de alfa (0 < alfa < 1): ";
  std::cin >> alfa;
  if (alfa <= 0 || alfa >= 1) {
    for (int gap = size/2; gap > 0; gap *= alfa) {
      for (int i = gap; i < size; i += 1) {
        Key temp = seq[i];
        int j;           
        for (j = i; j >= gap && seq[j - gap] > temp; j -= gap)
        seq[j] = seq[j - gap];
      seq[j] = temp;
      }
      if (trace) seq.Print();
    }
  } else {
  std::cout << "El valor de alfa esta fuera de: 0 < alfa < 1." << std::endl;
  }
}

/** ---------------------------------------------------------------------------------------------------
 * @brief Función que obtiene el valor máximo de un vector de elementos
 * @param seq Vector de elementos
 * @param size Tamaño del vector
 */
template <class Key>
int getMax(StaticSequence<Key>& seq, int size) {
  Key max = seq[0];
  for (int i = 1; i < size; i++)
    if (seq[i] > max)
      max = seq[i];
  return max;
}

/**
 * @brief Función que cuenta los elementos de un vector de elementos
 * @param seq Vector de elementos
 * @param size Tamaño del vector
 * @param exp Exponente
 * @param trace Indica si se debe imprimir el vector en cada paso
*/
template <class Key>
void countSort(StaticSequence<Key>& seq, int size, int exp, bool trace) {
  Key output[size];
  int count[10] = {0};

  for (int i = 0; i < size; i++)
    count[(seq[i] / exp) % 10]++;

  for (int i = 1; i < 10; i++)
    count[i] += count[i - 1];

  for (int i = size - 1; i >= 0; i--) {
    output[count[(seq[i] / exp) % 10] - 1] = seq[i];
    count[(seq[i] / exp) % 10]--;
  }

  for (int i = 0; i < size; i++)
    seq[i] = output[i];
  
  if (trace) seq.Print();
}

/**
 * @brief Función que ordena un vector de elementos utilizando el algoritmo de radixsort
 * @param seq Vector de elementos
 * @param size Tamaño del vector
 * @param trace Indica si se debe imprimir el vector en cada paso
 */
template <class Key>
void radixsort(StaticSequence<Key>& seq, int size, bool trace) {
  Key max = getMax(seq, size);
  for (int exp = 1; max / exp > 0; exp *= 10)
    countSort(seq, size, exp, trace);
}

#endif