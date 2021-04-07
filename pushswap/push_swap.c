/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hchorfi <hchorfi@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 11:33:01 by hchorfi           #+#    #+#             */
/*   Updated: 2021/04/07 18:40:25 by hchorfi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list   *ft_init_stacks(int argc, char **argv, int stack)
{
    t_list  *a;
    t_list  *b;
    int     i;
    int     *val;
    
    i = 1;
    b = NULL;
    a = NULL;
    if (stack == 0)
    {
        printf("b : %p\n", b);
        return (b);
    }
    else
    {
        while (argv[i])
        {
            val = malloc(sizeof(int));
            *val = ft_atoi(argv[i]);
            if (a == NULL)
                a = ft_lstnew(val);
            else
                ft_lstadd_back(&a, ft_lstnew(val));
            i++;            
        }
        printf("a : %p\n", a);
        return (a);
    }
}

void    ft_print_stacks(t_list **a_head, t_list **b_head)
{
    printf("a : %p\n", *a_head);
    printf("b : %p\n", *b_head);
    t_list  *a;
    t_list  *b;
    a = *a_head;
    b = *b_head;
    while (a)
    {
        printf("%10d", *(int *)a->content);
        if(b)
        {
            printf("  %10d\n", *(int *)b->content);
            b = b->next;
        }
        else
            printf(" \n");
        a = a->next;
    }
    printf("----------  ----------\n");
    printf("(stack  a)  (stack b )\n");
    printf("----------------------\n");

}

void    ft_swap_stack(t_list **stack)
{
    int *tmp;
    if (ft_lstsize(*stack) > 1)
    {
        tmp = (*stack)->content;
        (*stack)->content = (*stack)->next->content;
        (*stack)->next->content = tmp;
    }
}

void    ft_ss(t_list **a, t_list **b)
{
    ft_swap_stack(*(&a));
    ft_swap_stack(*(&b));
}

int     ft_del_list(t_list **head, int position)
{
    t_list *curr;
    t_list *prev;
    
    curr = *head;
    prev = *head;
    if (*head == NULL)
        return (0);
    else if (position == 1)
    {
        *head = curr->next;
        free(curr);
        curr = NULL;
    }
    else
    {
        while (position != 1)
        {
            prev = curr;
            curr = curr->next;
            position--;
        }
        prev->next = curr->next;
        free(curr);
        curr = NULL; 
    }
    return (0);
}

void    ft_pb(t_list **a, t_list **b)
{
    int *val;

    if (ft_lstsize(*a) > 0)
    {
        if (*b == NULL)
            *b = ft_lstnew((*a)->content);
        else
        {
            ft_lstadd_front(*(&b), ft_lstnew((*a)->content));
        }
        ft_del_list(*(&a), 1);
    }
}

void    ft_pa(t_list **a, t_list **b)
{
    int *val;

    if (ft_lstsize(*b) > 0)
    {
        if (*a == NULL)
            *a = ft_lstnew((*b)->content);
        else
        {
            ft_lstadd_front(*(&a), ft_lstnew((*b)->content));
        }
        ft_del_list(*(&b), 1);
    }
}

void    ft_rot_stack(t_list **stack)
{
    if (ft_lstsize(*stack) > 1)
    {
        ft_lstadd_back(*(&stack), ft_lstnew((*stack)->content));
        ft_del_list(*(&stack), 1);
    }
}

void    ft_rr(t_list **a, t_list **b)
{
    ft_rot_stack(*(&a));
    ft_rot_stack(*(&b));
}

void    ft_rev_rot_stack(t_list **stack)
{
    t_list *stack_head;
    int size_stack;
    int i;

    i = 1;
    stack_head = *stack;
    size_stack = ft_lstsize(*stack);
    if ( size_stack > 1)
    {
        while (i <= size_stack)
        {
            if (i == size_stack)
            {
                ft_lstadd_front(*(&stack), ft_lstnew(stack_head->content));
                ft_del_list(*(&stack), size_stack + 1);
                break;
            }
            i++;
            stack_head = stack_head->next;
        }
    }
}

void    ft_rrr(t_list **a, t_list **b)
{
    ft_rev_rot_stack(*(&a));
    ft_rev_rot_stack(*(&b));
}

int    ft_check_stack_ops(t_list **a, t_list **b)
{
    char *line;

    printf("a : %p\n", *a);
    printf("b : %p\n", *b);
    while (1)
    {
        get_next_line(1, &line);
        if (!strcmp(line, "sa"))
        {
            ft_swap_stack(*(&a));
        }
        else if (!strcmp(line, "sb"))
        {
            ft_swap_stack(*(&b));
        }
        else if (!strcmp(line, "ss"))
        {
            ft_ss(*(&a), *(&b));
        }
        else if (!strcmp(line, "pb"))
        {
            ft_pb(*(&a), *(&b));
        }
        else if (!strcmp(line, "pa"))
        {
            ft_pa(*(&a), *(&b));
        }
        else if (!strcmp(line, "ra"))
        {
            ft_rot_stack(*(&a));
        }
        else if (!strcmp(line, "rb"))
        {
            ft_rot_stack(*(&b));
        }
        else if (!strcmp(line, "rr"))
        {
            ft_rr(*(&a), *(&b));
        }
        else if (!strcmp(line, "rra"))
        {
            ft_rev_rot_stack(*(&a));
        }
        else if (!strcmp(line, "rrb"))
        {
            ft_rev_rot_stack(*(&b));
        }
        else if (!strcmp(line, "rrr"))
        {
            ft_rrr(*(&a), *(&b));
        }
        else
        {
            printf("Error\n");
            return (1);
        }
        ft_print_stacks(*(&a), *(&b));
    }
    return (0);
}


int main(int argc, char **argv)
{
    t_list  *a;
    t_list  *b;
    
    if (argc == 1)
        return (0);
    else if (ft_check_error(argc, argv))
    {
        ft_putstr_fd("error\n", 1);
        return (1);
    }
    a = ft_init_stacks(argc, argv, 1);
    b = ft_init_stacks(argc, argv, 0);
    printf("a : %p\n", a);
    printf("b : %p\n", b);
    printf("init stacks\n");
    ft_print_stacks(&a, &b);
    if (ft_check_stack_ops(&a, &b))
        return (1);
    return (0);
}
