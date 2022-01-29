
#include <stdlib.h>
#include "headers/tokens.h"

Token *token_init(int type, char *value)
{
	Token *token = calloc(1, sizeof(Token));
	token->type = type;
	token->value = value;
	return token;
}
