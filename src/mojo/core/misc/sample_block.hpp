#ifndef MOJO_SAMPLE_BLOCK_H
#define MOJO_SAMPLE_BLOCK_H

float*
sample_block_alloc(size_t block_size);

/// allocate and silence block
float*
sample_block_calloc(size_t block_size);

void
sample_block_free(float*);

void
sample_blocks_realloc(std::vector<float*>& blocks, size_t new_block_size);

void
sample_block_silence(float* block, size_t block_size);

void
sample_blocks_silence(std::vector<float*>& blocks, size_t block_size);

#endif // MOJO_SAMPLE_BLOCK_H
