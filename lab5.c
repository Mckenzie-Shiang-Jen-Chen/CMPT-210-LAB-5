#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next,
                      int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
  struct header *current = free_list_ptr;
  while (current != NULL) {
    if (current->size >= size) {
      return current->id;
    }
    current = current->next;
  }
  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  struct header *current = free_list_ptr;
  int best_fit_id = -1;
  uint64_t min = UINT64_MAX;

  while (current != NULL) {
    if (current->size >= size && current->size < min) {
      min = current->size;
      best_fit_id = current->id;
    }
    current = current->next;
  }
  return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  struct header *current = free_list_ptr;
  int worst_fit_id = -1;
  uint64_t max = 0;

  while (current != NULL) {
    if (current->size >= size && current->size > max) {
      max = current->size;
      worst_fit_id = current->id;
    }
    current = current->next;
  }
  return worst_fit_id;
}

int main(void) {

  struct header *free_block1 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block2 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block3 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block4 = (struct header *)malloc(sizeof(struct header));
  struct header *free_block5 = (struct header *)malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  printf("The ID for First-Fit algorithm is: %d\n", first_fit_id);
  printf("The ID for Best-Fit algorithm is: %d\n", best_fit_id);
  printf("The ID for Worst-Fit algorithm is: %d\n", worst_fit_id);

  free(free_block1);
  free(free_block2);
  free(free_block3);
  free(free_block4);
  free(free_block5);

  return 0;
}

/* Part 2: Coalescing Contiguous Free Blocks
 *
 * Input:
 * - pointer: the pointer to the block currently being freed
 *
 * Variables:
 * - currentBlock: header for pointer
 * - nextBlock: the block after the currentBlock in memory
 * - previousBlock: the block before the currentBlock in memory
 * - nextFree: a boolean that indicate whether the next block is free
 * - previousFree: a boolean that indicate whether the previous block is free
 *
 * Initialize variables
 * - get the address of the currentBlock
 * - find the address of nextBlock
 * - check the status of nextBlock
 * - check the status of previousBlock
 *
 * if(nextFree == true AND previousFree == false)
 * since next block is not free, remove next block from the list
 * currentBlock.size = currentBlock.size + nextBlock.size
 * update the header of currentBlock with new size
 * return
 *
 * if(nextFree == false AND previousFree == true)
 * previousBlock.size = previousBlock.size + currentBlock.size
 * update the header of previousBlock with new size
 * return
 *
 *
 */
