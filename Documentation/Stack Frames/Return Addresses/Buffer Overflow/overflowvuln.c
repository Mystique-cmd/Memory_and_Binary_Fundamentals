#include <stdio.h>
#include <string.h>

#define LOGICAL_CAPACITY 16
#define ARENA_CAPACITY 24

/* A bounded example of crossing a logical boundary into adjacent marker data.
   Input remains within the backing array; this does not overwrite a return address. */
struct demo_state {
	char arena[ARENA_CAPACITY];
};

static void demonstrate_adjacent_data(struct demo_state *state)
{
	memset(state, 0, sizeof(*state));
	memset(state->arena + LOGICAL_CAPACITY, 'M', ARENA_CAPACITY - LOGICAL_CAPACITY);

	puts("Enter up to 23 non-whitespace characters:");
	if (scanf("%23s", state->arena) == 1) {
		printf("Input: %s\n", state->arena);
		printf("Adjacent marker: %.8s\n", state->arena + LOGICAL_CAPACITY);
	}
}

int main(void)
{
	struct demo_state state;
	demonstrate_adjacent_data(&state);
	return 0;
}


