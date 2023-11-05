#include <stdio.h>

enum comment_state
{
    NOT_COMMENT,
    INLINE_COMMENT,
    BLOCK_COMMENT
};

int main(void)
{
    enum comment_state state = NOT_COMMENT;
    int last = getchar();
    int c;

    if (EOF == last)
        return 0;

    while ((c = getchar()) != EOF)
    {
        switch (state)
        {
        case NOT_COMMENT:
            if ('/' == last)
            {
                if ('/' == c)
                    state = INLINE_COMMENT;
                else if ('*' == c)
                    state = BLOCK_COMMENT;
            }
            break;
        
        case INLINE_COMMENT:
            if ('\n' == c)
                state = NOT_COMMENT;
            break;

        case BLOCK_COMMENT:
            if ('*' == last && '/' == c)
            {
                last = getchar();
                if (EOF == last)
                    break;

                state = NOT_COMMENT;
                continue;
            }
            break;
        }

        if (NOT_COMMENT == state)
            putchar(last);

        last = c;
    }

    if (NOT_COMMENT == state)
        putchar(last);

    return 0;
}