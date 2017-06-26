#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// -----------------------------------------------------------------------------
// vl_draw API definition
// -----------------------------------------------------------------------------

/**
 * @brief Structure for holding the data of a virtual display
 */
typedef struct _display {
    int x;        //!< The width of the virtual screen
    int y;        //!< The height of the virtual screen
    char* buffer; //!< Buffer holding display's data
} display;

typedef display* display_ptr;

/**
 * @brief Creates a new virtual display
 * @param x Size x
 * @param y Size y
 * @return NULL or a valid display address
 */
display_ptr vl_create_display(int x, int y);

/**
 * @brief Clears display with supplied character 'c'
 * @param p_display Display
 * @param c Fill character
 */
void vl_clear_display(display_ptr p_display, char c);

/**
 * @brief Prints contents of the display to the out stream
 * @param p_display Display to print
 * @param out A valid text output stream
 */
void vl_print_display(display_ptr p_display, FILE* out);

/**
 * @brief Frees all resources allocated by the 'vl_create_display' call
 * @param pp_display Pointer to the display instance
 */
void vl_delete_display(display_ptr* pp_display);

/**
 * @brief Draws a triangle of height 'height' at (pos_x, pos_y)
 * @param p_display Display instance
 * @param height Height of the triangle
 * @param pos_x x-coordinate
 * @param pos_y y-coordinate
 */
void vl_draw_triangle(display_ptr p_display, int height, int pos_x, int pos_y);

/**
 * @brief Draws a point at (pos_x, pos_y)
 * @param p_display Display instance
 * @param c Character to draw
 * @param pos_x x-coordinate
 * @param pos_y y-coordinate
 */
void vl_draw_point(display_ptr p_display, char c, int pos_x, int pos_y);

// -----------------------------------------------------------------------------
// vl_draw API implementation
// -----------------------------------------------------------------------------

display_ptr vl_create_display(int x, int y) {
    if(x < 1 || y < 1)
        return NULL;

    display_ptr m_d = (display_ptr)malloc(sizeof(display));
    if(m_d) {
        m_d->x = x;
        m_d->y = y;
        m_d->buffer = (char*)calloc(x * y, sizeof(char));
        if(m_d->buffer)
            return m_d;
        else
            free(m_d);
    }

    return NULL;
}

void vl_delete_display(display_ptr* pp_display) {
    assert(pp_display != NULL);
    if(!pp_display)
        return;

    assert(*pp_display != NULL);
    if(!*pp_display)
        return;

    free((*pp_display)->buffer);
    free(*pp_display);

    *pp_display = NULL;
}

void vl_clear_display(display_ptr p_display, char c) {
    assert(p_display != NULL);
    if(!p_display)
        return;

    for(int i = 0; i < p_display->x * p_display->y; i++)
        p_display->buffer[i] = c;
}

void vl_print_display(display_ptr p_display, FILE* out) {
    assert(p_display != NULL);
    assert(out != NULL);
    if(!p_display || !out)
        return;

    for(int y = 0; y < p_display->y; y++) {
        for(int x = 0; x < p_display->x; x++) {
            assert(y * p_display->x + x < p_display->x * p_display->y);
            fprintf(out, "%c", p_display->buffer[y * p_display->x + x]);
        }
        fprintf(out, "\n");
    }
}

void vl_draw_point(display_ptr p_display, char c, int pos_x, int pos_y) {
    assert(p_display != NULL);
    if(!p_display)
        return;

    if(pos_x < 0 || pos_y < 0)
        return;

    if(pos_x > (p_display->x - 1) || pos_y > (p_display->x - 1))
        return;

    assert(pos_y * p_display->x + pos_x < p_display->x * p_display->y);
    if(pos_y * p_display->x + pos_x < p_display->x * p_display->y)
        p_display->buffer[pos_y * p_display->x + pos_x] = c;
}

void vl_draw_triangle(display_ptr p_display, int height, int pos_x, int pos_y) {
    assert(p_display != NULL);
    if(!p_display)
        return;

    if(pos_x < 0 || pos_y < 0)
        return;

    if(height < 1)
        return;

    int row_lenght = 2 * height - 1;
    int stars = 0;
    int pos_begin = 0;
    int pos_end = 0;

    if((pos_x + row_lenght > p_display->x) && (pos_y + height > p_display->y))
        return;

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < row_lenght; x++) {
            stars = 2 * (y + 1) - 1;
            pos_begin = (row_lenght - stars) / 2;
            pos_end = row_lenght - pos_begin;

            if((x >= pos_begin) && (x < pos_end))
                vl_draw_point(p_display, '*', x + pos_x, y + pos_y);
        }
    }
}

// -----------------------------------------------------------------------------
// vl_utility API definition
// -----------------------------------------------------------------------------

/**
 * @brief Checks if the string 'p_str' contains only numerical values
 * @param p_str Non NULL string to check
 * @return 0 if the string contains only digits and non-zero value otherwise
 */
int vl_check_number_string(char* p_str);

// -----------------------------------------------------------------------------
// vl_utility API implementation
// -----------------------------------------------------------------------------

int vl_check_number_string(char* p_str) {
    assert(p_str != NULL);
    if(p_str == NULL)
        return 2;

    // - Expect a null terminated string
    while(*p_str) {
        if(isdigit(*(p_str++)) == 0)
            return 1;
    }

    return 0;
}

// -----------------------------------------------------------------------------
// Sierpinski code
// -----------------------------------------------------------------------------

void print_recursive_sierpinski(display_ptr p_display,
                                int height,
                                int pos_x,
                                int pos_y,
                                int fractal_levels) {
    if(height < 2 || fractal_levels < 1)
        return;

    height /= 2;
    int lenght = 2 * height - 1;

    int triangle_vertices[3][2] = {{pos_x + lenght / 2 + 1, pos_y},
                                   {pos_x, pos_y + height},
                                   {pos_x + lenght + 1, pos_y + height}};

    print_recursive_sierpinski(p_display,
                               height,
                               triangle_vertices[0][0],
                               triangle_vertices[0][1],
                               fractal_levels - 1);
    print_recursive_sierpinski(p_display,
                               height,
                               triangle_vertices[1][0],
                               triangle_vertices[1][1],
                               fractal_levels - 1);
    print_recursive_sierpinski(p_display,
                               height,
                               triangle_vertices[2][0],
                               triangle_vertices[2][1],
                               fractal_levels - 1);

    if(fractal_levels == 1) {
        vl_draw_triangle(p_display,
                         height,
                         triangle_vertices[0][0],
                         triangle_vertices[0][1]);
        vl_draw_triangle(p_display,
                         height,
                         triangle_vertices[1][0],
                         triangle_vertices[1][1]);
        vl_draw_triangle(p_display,
                         height,
                         triangle_vertices[2][0],
                         triangle_vertices[2][1]);
    }
}

/**
 * @brief Prints a Sierpinski triangle of height 'height' and fractal levels
 * 'fractal_levels'
 * @param display Display instance
 * @param height Height of the triangle
 * @param fractal_levels Fractal levels to use
 */
void print_sierpinski_triangle(display_ptr p_display,
                               int height,
                               int fractal_levels) {
    if(height < 1 || fractal_levels < 0)
        return;

    // - Check if the height is divisible by 2 to the power of fractal levels
    if(height % (1 << fractal_levels) != 0)
        return;

    if(fractal_levels == 0)
        vl_draw_triangle(p_display, height, 0, 0);
    else
        print_recursive_sierpinski(p_display, height, 0, 0, fractal_levels);
}

int main(int argc, char** argv) {
    assert(argc >= 1);
    if(argc < 3) {
        printf("ERROR: Missing arguments!\n");
        printf("Syntax:\t%s height fractal_level, height [int], fractal_level "
               "[int]\n",
               argv[0]);
        return EXIT_FAILURE;
    } else if(argc > 3) {
        printf("ERROR: Extraneous arguments!\n");
        printf("Syntax:\t%s height fractal_level, height [int], fractal_level "
               "[int]\n",
               argv[0]);
        return EXIT_FAILURE;
    }

    assert(argc == 3);
    if(vl_check_number_string(argv[1]) != 0) {
        printf("ERROR: Positive integer argument expected!\n");
        printf("Syntax:\t%s height fractal_level, height [int], fractal_level "
               "[int]\n",
               argv[0]);
        return EXIT_FAILURE;
    }

    if(vl_check_number_string(argv[2]) != 0) {
        printf("ERROR: Positive integer argument expected!\n");
        printf("Syntax:\t%s height fractal_level, height [int], fractal_level "
               "[int]\n",
               argv[0]);
        return EXIT_FAILURE;
    }

    // - This is not a limitation of the program but a limitation of the
    // - screen space to display that amount of information
    if(strlen(argv[1]) > 3) {
        printf("WARNING: Integer argument is too large!\n");
        printf("Syntax:\t%s height fractal_level, height [int], fractal_level "
               "[int]\n",
               argv[0]);
        return EXIT_FAILURE;
    }

    if(strlen(argv[2]) > 2) {
        printf("WARNING: Integer argument is too large!\n");
        printf("Syntax:\t%s height fractal_level, height [int], fractal_level "
               "[int]\n",
               argv[0]);
        return EXIT_FAILURE;
    }

    int u_height = atoi(argv[1]);
    if(u_height < 1) {
        printf("WARNING: Integer argument is too small!\n");
        printf("Syntax:\t%s height fractal_level, height [int], fractal_level "
               "[int]\n",
               argv[0]);
        return EXIT_FAILURE;
    }

    int u_fractal = atoi(argv[2]);
    if(u_fractal < 0) {
        printf("WARNING: Integer argument is too small!\n");
        printf("Syntax:\t%s height fractal_level, height [int], fractal_level "
               "[int]\n",
               argv[0]);
        return EXIT_FAILURE;
    }

    else if(u_fractal > 30) {
        printf("WARNING: Integer argument is too large!\n");
        printf("Syntax:\t%s height fractal_level, height [int], fractal_level "
               "[int]\n",
               argv[0]);
        return EXIT_FAILURE;
    }

    int m_screen_x = 2 * u_height - 1;
    int m_screen_y = u_height;

    // - Check height divisibility property
    if(u_height % (1 << u_fractal) != 0) {
        printf("ERROR: Height must be divisible by 2^(fractal levels)!\n");
        return EXIT_FAILURE;
    }

    display_ptr m_screen = vl_create_display(m_screen_x, m_screen_y);

    if(m_screen == NULL) {
        printf("Failed to allocate memory required for storing virtual screen "
               "space\n");
        return EXIT_FAILURE;
    }

    vl_clear_display(m_screen, ' ');
    print_sierpinski_triangle(m_screen, u_height, u_fractal);
    vl_print_display(m_screen, stdout);
    vl_delete_display(&m_screen);

    return EXIT_SUCCESS;
}
