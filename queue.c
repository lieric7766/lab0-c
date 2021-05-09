#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "harness.h"


/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q == NULL) {
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q == NULL) {
        return;
    }
    while (q->head != NULL) {
        list_ele_t *tmp_q_head = q->head->next;
        free(q->head->value);
        free(q->head);
        q->head = tmp_q_head;
    }
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL) {
        return false;
    }

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));

    if (newh == NULL) {
        return false;
    }

    size_t s_len = strlen(s);
    newh->value = malloc(s_len + 1);

    if (newh->value == NULL) {
        free(newh);
        return false;
    }

    memcpy(newh->value, s, s_len);
    newh->value[s_len] = '\0';

    if (q->head == NULL) {
        q->head = newh;
        q->tail = newh;
        newh->next = NULL;
        q->size++;
    } else {
        newh->next = q->head;
        q->head = newh;
        q->size++;
    }

    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (q == NULL) {
        return false;
    }

    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));

    if (newt == NULL) {
        return false;
    }

    size_t s_len = strlen(s);
    newt->value = malloc(s_len + 1);

    if (newt->value == NULL) {
        free(newt);
        return false;
    }

    memcpy(newt->value, s, s_len);
    newt->value[s_len] = '\0';
    newt->next = NULL;

    if (q->tail == NULL) {
        if (q->head == NULL) {
            q->head = newt;
        }
        q->tail = newt;
        q->size++;
    } else {
        q->tail->next = newt;
        q->tail = newt;
        q->size++;
    }

    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q == NULL || q->head == NULL) {
        return false;
    }

    if (sp) {
        size_t len = strlen(q->head->value) + 1;
        len = len > bufsize ? bufsize : len;
        strncpy(sp, q->head->value, len);
        sp[len - 1] = '\0';
    }

    list_ele_t *tmp = q->head;

    q->head = q->head->next;
    q->size--;
    free(tmp->value);
    free(tmp);
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q == NULL) {
        return 0;
    }
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */

    if (q == NULL) {
        return;
    }

    list_ele_t *prev_element = NULL;
    list_ele_t *current_element = q->head;
    q->tail = q->head;
    while (current_element != NULL) {
        list_ele_t *tmp_element = current_element->next;
        current_element->next = prev_element;
        prev_element = current_element;
        current_element = tmp_element;
    }
    q->head = prev_element;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */

    if (q == NULL || q->head == NULL) {
        return;
    }
    list_ele_t *main_array[q->size];
    list_ele_t *tmp_ele;
    tmp_ele = q->head;
    for (int i = 0; i < q->size; ++i) {
        main_array[i] = tmp_ele;
        if (tmp_ele->next != NULL) {
            tmp_ele = tmp_ele->next;
        }
    }

    merge_sort(main_array, 0, q->size - 1, q->size);
    for (int i = 0; i < q->size; ++i) {
        if (i == 0) {
            q->head = main_array[i];
        }

        if (i == q->size - 1) {
            q->tail = main_array[i];
            main_array[i]->next = NULL;
            break;
        }

        if ((i + 1) < q->size) {
            main_array[i]->next = main_array[i + 1];
        }
    }
}

void merge(list_ele_t *arr[], int left, int right, int arr_size)
{
    int l_start = left;
    int mid = (l_start + right) / 2 + 1;
    int r_start = mid;
    list_ele_t *tmp_arr[arr_size];

    for (int i = left; i <= right; ++i) {
        if (r_start > right) {
            tmp_arr[i] = arr[l_start];
            l_start++;
            continue;
        }
        if (l_start >= mid) {
            tmp_arr[i] = arr[r_start];
            r_start++;
            continue;
        }
        if (*arr[r_start]->value <= *arr[l_start]->value) {
            tmp_arr[i] = arr[r_start];
            r_start++;
            continue;
        }
        if (*arr[r_start]->value > *arr[l_start]->value) {
            tmp_arr[i] = arr[l_start];
            l_start++;
            continue;
        }
    }
    for (int i = left; i <= right; ++i) {
        arr[i] = tmp_arr[i];
    }
}


void merge_sort(list_ele_t *arr[], int left, int right, int arr_size)
{
    if (left == right)
        return;

    int mid = (left + right) / 2;
    merge_sort(arr, left, mid, arr_size);
    merge_sort(arr, mid + 1, right, arr_size);
    merge(arr, left, right, arr_size);
}
