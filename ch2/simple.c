#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/string.h>
#include<linux/slab.h>
static LIST_HEAD(birthday_list); //this macro defines and initializes the variable birthday_list

/*structure for list*/
struct birthday {
//char *name = NULL;
int day;
int month;
int year;
struct list_head list;
};

//void setbirthday(struct birthday *person,char *name, int day, int month, int year);
void setbirthday(struct birthday *person, int day, int month, int year);

/* This function is called when the module is loaded. */
int simple_init(void)
{
    struct birthday *ptr;
    
    printk(KERN_INFO "Loading Module Simple\n");

    struct birthday *bob, *shyam, *hari, *abhi, *ashish;

    bob = kmalloc(sizeof(*bob),GFP_KERNEL);
    shyam = kmalloc(sizeof(*shyam),GFP_KERNEL);
    hari = kmalloc(sizeof(*hari),GFP_KERNEL);
    abhi = kmalloc(sizeof(*abhi),GFP_KERNEL);
    ashish = kmalloc(sizeof(*ashish),GFP_KERNEL);
    
    setbirthday(bob, 10, 3, 1990);
    setbirthday(shyam, 11, 4, 1991);
    setbirthday(hari, 12, 5, 1992);
    setbirthday(abhi, 13, 6, 1993);
    setbirthday(ashish, 14, 7, 1994);
    
    /*Traversing the linked list and printing the birthday*/
    list_for_each_entry(ptr, &birthday_list, list){
    /*on each iteration ptr points to the next birthday struct*/
printk(KERN_INFO "adding born on day: %d month: %d year: %d\n",ptr->day,ptr->month,ptr->year);    
}    
    return 0;
}

void setbirthday(struct birthday *person, int day, int month, int year)
{
/*creating and initializing instances of struct birthday*/
person->day = day;
person->month = month;
person->year = year;

/*initializing the list member in struct birthday*/
INIT_LIST_HEAD(&person->list);  

/*Inserting Elements into the Linked List*/
list_add_tail(&person->list,&birthday_list);
}

/* This function is called when the module is removed. */
void simple_exit(void) 
{
printk(KERN_INFO "Removing Module\n");

struct birthday *ptr, *next;
list_for_each_entry_safe(ptr,next,&birthday_list,list){
printk(KERN_INFO "removing born on day: %d month: %d year: %d\n",ptr->day,ptr->month,ptr->year); 

/*on each iteration ptr points to the next birthday struct*/
list_del(&ptr->list);
kfree(ptr);
}
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
