#include "matcher.h"

int is_operater(char c) {
    if (c == '+' || c == '.' || c == '?' || c == '\\') {
        return 1;
    }
    return 0;
}

/**
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
int matches_leading(char *partial_line, int line_length, char *pattern, int pattern_length) {
    // base case: 
    if (*pattern == '\0') {
        return 1;
    }
    if (*partial_line == '\0') {
        return 0;
    }
    // if *Partial_line is not a operator, recursively call the matches_leading(partial_line + 1, pattern + 1)
    
    if (*pattern == '\\') {
        if (*(pattern + 1) == *partial_line) {
            return matches_leading(partial_line + 1, line_length - 1, pattern + 2, line_length - 2);
        }
        return 0;
    } else if (*pattern == '.') {
        return matches_leading(partial_line + 1, line_length - 1, pattern + 1, pattern_length - 1);
    } else if (*pattern == '+') {
        while (*partial_line == *(partial_line + 1) && line_length > pattern_length) {
            partial_line++;
            line_length -= 1;
        }
        return matches_leading(partial_line + 1, line_length - 1, pattern + 1, pattern_length - 1); 
    } else {
        if (*partial_line == *pattern) {
            if (*(pattern + 1) == '?') {
                return matches_leading(partial_line, line_length, pattern + 2, pattern_length - 2) || matches_leading(partial_line + 1, line_length - 1, pattern + 2, pattern_length - 2);
            }
            return matches_leading(partial_line + 1, line_length - 1, pattern + 1, pattern_length - 1);
        } else if (*(pattern + 1) == '?') {
            return matches_leading(partial_line, line_length, pattern + 2, pattern_length - 2);
        }
        return 0;
    }
    return 0;
}

/**
 * Implementation of your matcher function, which
 * will be called by the main program.
 *
 * You may assume that both line and pattern point
 * to reasonably short, null-terminated strings.
 */
int rgrep_matches(char *line, char *pattern) {
    char *p = line;
    char *q = pattern;
    int len1 = 0;
    int len2 = 0;
    while (*(p++) != '\0') {
        len1++;
    }
    while (*(q++) != '\0') {
        len2++;
    }
    while (*line != '\0') {
        if (matches_leading(line, len1, pattern, len2)) {
            return 1;
        }
        line++;
    }
    return 0;
}
