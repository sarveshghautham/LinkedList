//
//  main.c
//  LinkedList
//
//  Created by Sarvesh Ghautham on 2/22/14.
//

#include "main.h"

int main(int argc, const char * argv[])
{

    FILE *fp = NULL;  //For writing the lists.
    FILE *fp1 = NULL; //For writing the list ids.

    int i=0;
    int count=0;
    int index=0;
    int data=0;
    int list_number=0;
    int count_lists=0;
    long list_length=0;
    long list_id_length=0;
    int list_count=0;
    int result=0;
    int arr_list_id[MAX_LISTS];
    char ch;
    node *head=NULL;
    node *head_mem[MAX_LISTS];

    count_lists=0;
   
    if (argc == 1)
    {
        printf("\n Enter at least one argument \n");
        exit(1);
    }
    
    //line_count = number_of_lines_count_in_file("list.out");
    list_number = atoi(argv[2]);
    list_id_length = get_list_id(&fp1, arr_list_id, &list_count);
    
    
    if (strcmp(argv[1], "create") == 0)
    {
        printf ("\n creating a list \n");
        if (!check_line_number(arr_list_id, list_number, list_id_length))
        {
            data = atoi(argv[3]);
            head = create(list_number, data);
            write_to_file(head, &fp);
            write_list_number_file(&fp1, list_number, list_length);
        }

    }
    else if (strcmp(argv[1], "insert") == 0)
    {
        printf ("\n inserting into list \n");
    
        // Check to see if the  list_number is in arr_list_id
        if (!check_line_number(arr_list_id, list_number, list_count))
        {
            while (1)
            {
                printf("\n List doesn't exist. \n Do you want to create it? \n Type 'y' for YES or 'n' for NO \n");
                scanf("%c",&ch);
                
                if (ch == 'y' || ch == 'Y')
                {
                    printf("\n Creating... \n");
                    data = atoi(argv[3]);
                    head = create(list_number, data);
                    write_list_number_file(&fp1, list_number, list_length);
                    
                    if (argc == 4)
                        write_to_file(head, &fp);
                    else
                    {
                        for (i = 4; i < argc; i++ )
                        {
                            data = atoi(argv[i]);
                            insert(&head, list_number, data);
                            
                        }
                        write_to_file(head, &fp);
                    }
                    break;
                }
                else if (ch == 'n' || ch == 'Y')
                {
                    exit(1);
                }
                else
                {
                    printf ("\n Type 'y' for YES or 'n' for NO \n");
                }
            }
            
        }
        else
        {
            count = load_in_memory(&fp, head_mem);
            if (count == 1)
            {
                index = 0;
            }
            else if (count == 0)
            {
                while (1)
                {
                    printf("\n List doesn't exist. \n Do you want to create it? \n Type 'y' for YES or 'n' for NO \n");
                    scanf("%c",&ch);
                    
                    if (ch == 'y' || ch == 'Y')
                    {
                        printf("\n Creating... \n");
                        data = atoi(argv[3]);
                        head = create(list_number, data);
                        write_list_number_file(&fp1, list_number, list_length);
                        
                        if (argc == 4)
                            write_to_file(head, &fp);
                        else
                        {
                            for (i = 4; i < argc; i++ )
                            {
                                data = atoi(argv[i]);
                                insert(&head, list_number, data);
                                
                            }
                            write_to_file(head, &fp);
                        }
                        break;
                    }
                    else if (ch == 'n' || ch == 'n')
                    {
                        exit(1);
                    }
                    else
                    {
                        printf ("\n Type 'y' for YES or 'n' for NO \n");
                    }
                }
            }
            for (i = 0; i < count; i++)
            {
                if (head_mem[i]->list_id == list_number)
                {
                    index = i;
                    break;
                }
                
            }
        
            for (i = 3; i < argc; i++)
            {
                head = head_mem[index];
                data = atoi(argv[i]);
                insert(&head, list_number, data);
                head_mem[index] = head;
            }

            rewrite_to_file(head_mem, &fp, list_number, count);
        }
        
    }
    else if (strcmp(argv[1], "display") == 0)
    {
        printf ("\n displaying a list \n");
        if (check_line_number(arr_list_id, list_number, list_count))
        {
            head = read_from_file_and_construct_list(&fp, list_number, &list_length);
            display(head);
        }
        else
        {
            printf("\n List does not exist \n");
        }
    }
    else if (strcmp(argv[1], "remove_node") == 0)
    {
        if (check_line_number(arr_list_id, list_number, list_count))
        {
            printf ("\n Removing a node \n");
            data = atoi(argv[3]);
            count = load_in_memory(&fp, head_mem);
            if (count == 1)
            {
                index = 0;
            }
            else
            {
                for (i = 0; i < count; i++)
                {
                    if (head_mem[i]->list_id == list_number)
                    {
                        index = i;
                        break;
                    }
                }
                
            }
            if (check_node_present(head_mem[index], data))
            {
                
                for (i = 3; i < argc; i++)
                {
                    head = head_mem[index];
                    data = atoi(argv[i]);
                    result = remove_node(&head, data);
                    head_mem[index] = head;
                
                }
                if (head_mem[index] == NULL)
                {
                    remove_from_listid_file(&fp1, list_number);
                }
                
                rewrite_to_file(head_mem, &fp, list_number, count);
            }
            else
            {
                printf ("\n Node not found \n");
            }
        
        }
        else
        {
            printf("\n List does not exist\n");
        }
    
    }
    else if (strcmp(argv[1], "remove_list") == 0)
    {
        printf ("\n Removing a list \n");
        if (check_line_number(arr_list_id, list_number, list_count))
        {
            count = load_in_memory(&fp, head_mem);
            if (count == 1)
            {
                index = 0;
            }
            else if (count == 0)
            {
                printf("file is empty");
                exit(1);
            }
            else
            {
                for (i = 0; i < count; i++)
                {
                    if (head_mem[i]->list_id == list_number)
                    {
                        index = i;
                        break;
                    }
                    
                }
            }
            
            remove_list(head_mem[index]);
            remove_from_listid_file(&fp1, list_number);
            head_mem[index] = NULL;
            rewrite_to_file(head_mem, &fp, list_number, count);
        }
        else
        {
            printf("\n List does not exist\n");
        }
        
    }
    else
    {
        printf ("\n Invalid option \n");
    }
    
    return 0;
}


