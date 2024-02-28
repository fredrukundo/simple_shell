#include "shell.h"


void ft_memcpy(void *restrict_dst, const void *restrict_src, unsigned int n)
{
	char *char_ptr = (char *)restrict_src;
	char *char_newptr = (char *)restrict_dst;
	unsigned int i;

	for (i = 0; i < n; i++)
		char_newptr[i] = char_ptr[i];
}


void *ft_realloc(void *ptr, unsigned int old_n, unsigned int new_n)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_n));

	if (new_n == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_n == old_n)
		return (ptr);

	newptr = malloc(new_n);
	if (newptr == NULL)
		return (NULL);

	if (new_n < old_n)
		ft_memcpy(newptr, ptr, new_n);
	else
		ft_memcpy(newptr, ptr, old_n);

	free(ptr);
	return (newptr);
}


char **ft_reallocdp(char **ptr, unsigned int old_n, unsigned int new_n)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_n));

	if (new_n == old_n)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_n);
	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_n; i++)
		newptr[i] = ptr[i];

	free(ptr);

	return (newptr);
}
