namespace {

/*
 * 16 byte alignment is required for SSE but aligning
 * to cache line boundaries would be worth testing, perhaps
 * even page boundaries for some sizes.
 */
const size_t BYTE_ALIGNMENT = 16;
}

namespace mojo {

float* sample_block_alloc(size_t block_size)
{
	float* p = NULL;
	size_t alloc_size = block_size * sizeof(float);

#ifdef HAVE_POSIX_MEMALIGN
	if (posix_memalign((void**)&p, BYTE_ALIGNMENT, alloc_size) != 0) {
		p = NULL;
	}
#else
	p = (float*)malloc(alloc_size);
#endif

	return p;
}

float* sample_block_calloc(size_t block_size)
{
	float* s = sample_block_alloc(block_size);
	sample_block_silence(s, block_size);
	return s;
}

void sample_block_free(float* block)
{
	free(block);
}

void sample_blocks_realloc(std::vector<float*>& blocks, size_t new_block_size)
{
	if (new_block_size == 0) return;

	std::vector<float*>::iterator iter;

	for (iter = blocks.begin(); iter != blocks.end(); ++iter) {
		sample_block_free(*iter);
		*iter = sample_block_alloc(new_block_size);
	}
}

void sample_block_silence(float* block, size_t block_size)
{
	memset(block, 0, sizeof(float) * block_size);
}

void sample_blocks_silence(std::vector<float*>& blocks, size_t block_size)
{
	std::vector<float*>::iterator iter;

	for (iter = blocks.begin(); iter != blocks.end(); ++iter) {
		sample_block_silence(*iter, block_size);
	}
}

} // namespace mojo
