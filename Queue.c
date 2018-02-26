#include "Queue.h"

struct Queue_{
    Item *array;
    uint32_t maxSize;
    uint32_t head;
    uint32_t tail;
};

#ifdef DEBUG
static void queue_exit_error(char *msg){
    fprintf(stderr,"Queue.h --> %s\n",msg);
    fflush(stderr);
    exit(EXIT_FAILURE);
}
#endif //DEBUG

Queue queue_init(uint32_t maxSize){
    Queue out=malloc(sizeof(struct Queue_));
    #ifdef DEBUG
    if(out==NULL)
        queue_exit_error("queue_init(): malloc(sizeof(struct Queue_))==NULL");
    #endif //DEBUG
    out->maxSize=maxSize+1;
    out->array=malloc(sizeof(Item)*(maxSize+1));
    #ifdef DEBUG
    if(out->array==NULL)
        queue_exit_error("queue_init(): malloc(sizeof(Item)*(maxSize+1)");
    #endif // DEBUG
    out->head=0;
    out->tail=0;
    return out;
}

void queue_free(Queue in){
    #ifdef DEBUG
    if(in==NULL)
        return;
    if(in->array==NULL){
        free(in);
        return;
    }
    #endif //DEBUG
    free(in->array);
    free(in);
}

uint8_t queue_is_empty(Queue in){
    #ifdef DEBUG
    if(in==NULL)
        queue_exit_error("queue_is_empty(): in==NULL");
    #endif //DEBUG
    return in->head==in->tail;
}

uint8_t queue_is_full(Queue in){
    #ifdef DEBUG
    if(in==NULL)
        queue_exit_error("queue_is_full(): in==NULL");
    #endif //DEBUG
    if(in->tail+1==in->maxSize)
        return in->head==0;
    else
        return in->tail+1==in->head;

}

void queue_put_head(Queue in,Item item){
    #ifdef DEBUG
    if(in==NULL)
        queue_exit_error("queue_put_head(): in==NULL");
    if(queue_is_full(in))
        queue_exit_error("queue_put_head(): queue_is_full(in) is true");
    #endif //DEBUG
    if(!in->head)
        in->head=in->maxSize-1;
    else
        in->head--;
    in->array[in->head]=item;
}

void queue_put_tail(Queue in,Item item){
    #ifdef DEBUG
    if(in==NULL)
        queue_exit_error("queue_put_tail(): in==NULL");
    if(queue_is_full(in))
        queue_exit_error("queue_put_tail(): queue_is_full(in) is true");
    #endif //DEBUG
    in->array[in->tail]=item;
    in->tail++;
    if(in->tail==in->maxSize)
        in->tail=0;
}

Item queue_get(Queue in){
    #ifdef DEBUG
    if(in==NULL)
        queue_exit_error("queue_get(): in==NULL");
    if(queue_is_empty(in))
        queue_exit_error("queue_get(): queue_is_empty(in) is true");
    #endif //DEBUG
    return in->array[in->head];
}

Item queue_exctract(Queue in){
    Item out;
    #ifdef DEBUG
    if(in==NULL)
        queue_exit_error("queue_extract(): in==NULL");
    if(queue_is_empty(in))
        queue_exit_error("queue_get(): queue_is_empty(in) is true");
    #endif //DEBUG
    out=in->array[in->head];
    in->head++;
    if(in->head==in->maxSize)
        in->head=0;
    return out;
}

uint32_t queue_count(Queue in){
    #ifdef DEBUG
    if(in==NULL)
        queue_exit_error("queue_count(): in==NULL");
    #endif // DEBUG
    if(in->head>in->tail)
        return (in->maxSize-in->head)+in->tail;
    else
        return in->tail-in->head;
}

void queue_resize(Queue in,uint32_t maxSize){
    Item *temp;
    uint32_t i;
    #ifdef DEBUG
    if(in==NULL)
        queue_exit_error("queue_resize(): in==NULL");
    if(queue_count(in)>maxSize)
        queue_exit_error("queue_resize(): queue_count(in)>maxSize");
    #endif // DEBUG
    temp=malloc(sizeof(Item)*(maxSize+1));
    #ifdef DEBUG
    if(temp==NULL)
        queue_exit_error("queue_resize(): malloc(sizeof(Item)*(maxSize+1)");
    #endif // DEBUG
    for(i=0;!queue_is_empty(in);i++)
        temp[i]=queue_get(in);
    free(in->array);
    in->array=temp;
    in->head=0;
    in->tail=i;
}
