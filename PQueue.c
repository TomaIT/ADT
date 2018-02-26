#include "PQueue.h"

#define LEFT(i) ((i*2) + 1)
#define RIGHT(i) ((i*2) + 2)
#define PARENT(i) ((i-1) / 2)


struct PQueue_{
    Item *array;
    uint32_t size;
    uint32_t maxSize;
};

#ifdef DEBUG
static void pqueue_exit_error(char *msg){
    fprintf(stderr,"PQueue.h --> %s\n",msg);
    fflush(stderr);
    exit(EXIT_FAILURE);
}
#endif //DEBUG
static void swap(PQueue pq,uint32_t a,uint32_t b){
    Item temp;
    temp=pq->array[a];
    pq->array[a]=pq->array[b];
    pq->array[b]=temp;
}
static void HEAPify(PQueue h,uint32_t i){
    uint32_t l,r,largest;
    l=LEFT(i);
    r=RIGHT(i);
    if((l<h->size)&&(ItemGreater(h->array[l],h->array[i])))
        largest=l;
    else
        largest=i;
    if((r<h->size)&&(ItemGreater(h->array[r],h->array[largest])))
        largest=r;
    if(largest!=i){
        swap(h,i,largest);
        HEAPify(h,largest);
    }
}


PQueue pqueue_init(uint32_t maxSize){
    PQueue out;
    out=malloc(sizeof(struct PQueue_));
    #ifdef DEBUG
    if(out==NULL)
        pqueue_exit_error("pqueue_init(): malloc(sizeof(struct PQueue_))==NULL");
    #endif //DEBUG
    out->array=malloc(maxSize*sizeof(Item));
    #ifdef DEBUG
    if(out->array==NULL)
        pqueue_exit_error("pqueue_init(): malloc(maxSize*sizeof(Item))==NULL");
    #endif // DEBUG
    out->size=0;
    out->maxSize=maxSize;
    return out;
}

void pqueue_free(PQueue in){
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

uint8_t pqueue_is_empty(PQueue in){
    #ifdef DEBUG
    if(in==NULL)
        pqueue_exit_error("pqueue_is_empty(): in==NULL");
    #endif // DEBUG
    return in->size==0;
}

uint8_t pqueue_is_full(PQueue in){
    #ifdef DEBUG
    if(in==NULL)
        pqueue_exit_error("pqueue_is_full(): in==NULL");
    #endif // DEBUG
    return in->size==in->maxSize;
}

uint32_t pqueue_count(PQueue in){
    #ifdef DEBUG
    if(in==NULL)
        pqueue_exit_error("pqueue_size(): in==NULL");
    #endif // DEBUG
    return in->size;
}

void pqueue_insert(PQueue in,Item item){
    uint32_t i;
    #ifdef DEBUG
    if(in==NULL)
        pqueue_exit_error("pqueue_insert(): in==NULL");
    if(pqueue_is_full(in))
        pqueue_exit_error("pqueue_insert(): pqueue_is_full(in) is true");
    #endif // DEBUG
    i=in->size++;
    while((i>=1)&&(ItemGreater(item,in->array[PARENT(i)]))){
        in->array[i]=in->array[PARENT(i)];
        i=(i-1)/2;
    }
    in->array[i]=item;
}

Item pqueue_get(PQueue in){
    #ifdef DEBUG
    if(in==NULL)
        pqueue_exit_error("pqueue_get(): in==NULL");
    #endif // DEBUG
    return in->array[0];
}

Item pqueue_extract(PQueue in){
    Item item;
    #ifdef DEBUG
    if(in==NULL)
        pqueue_exit_error("pqueue_extract(): in==NULL");
    if(pqueue_is_empty(in))
        pqueue_exit_error("pqueue_extract(): pqueue_is_empty(in) is true");
    #endif // DEBUG
    in->size--;
    swap(in,0,in->size);
    item=in->array[in->size];
    HEAPify(in,0);
    return item;
}

void pqueue_resize(PQueue in,uint32_t maxSize){
    Item *temp;
    uint32_t i;
    #ifdef DEBUG
    if(in==NULL)
        pqueue_exit_error("pqueue_resize(): in==NULL");
    if(in->size>maxSize)
        pqueue_exit_error("pqueue_resize(): in->size>maxSize");
    #endif // DEBUG
    temp=malloc(sizeof(Item)*(maxSize));
    #ifdef DEBUG
    if(temp==NULL)
        pqueue_exit_error("pqueue_resize(): malloc(sizeof(Item)*(maxSize)");
    #endif // DEBUG
    for(i=0;i<in->size;i++)
        temp[i]=in->array[i];
    free(in->array);
    in->array=temp;
    in->maxSize=maxSize;
}
