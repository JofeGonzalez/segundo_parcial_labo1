#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
	LinkedList* this= NULL;
	this = (LinkedList*) malloc(sizeof(LinkedList));
	this->size=0;
	return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
	int returnAux = -1;
	if(this!= NULL)
	{
		returnAux=this->size;
	}
	return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* pNode=NULL;
	int i;

	if(this != NULL && nodeIndex<ll_len(this)&& ll_len(this)>0 && nodeIndex>=0)
	{
		pNode=this->pFirstNode;
		for(i=0; i<nodeIndex; i++)
		{
			pNode= pNode->pNextNode;
		}
	}
	return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
	Node* nuevoNode= NULL;
	Node* auxNode=NULL;
	Node* anteriorNode=NULL;
	int returnAux = -1;
	int i=0;
	if(this!=NULL && nodeIndex>=0 && nodeIndex<=ll_len(this))
	{
		nuevoNode = (Node*)malloc(sizeof(Node));
		if(nuevoNode!=NULL)
		{
			nuevoNode->pElement=pElement;
			nuevoNode->pNextNode=NULL;

			if(ll_isEmpty(this))
			{
				this->pFirstNode= nuevoNode;


			}else if(nodeIndex!=0)
			{
				auxNode=this->pFirstNode;

				while(auxNode!=NULL && i!= nodeIndex)
				{
					anteriorNode=auxNode;
					auxNode=auxNode->pNextNode;
					i++;
				}
				nuevoNode->pNextNode= auxNode;
				anteriorNode->pNextNode=nuevoNode;
			}else
			{
				nuevoNode->pNextNode=this->pFirstNode;
				this->pFirstNode= nuevoNode;
			}
		}
			returnAux=0;
			this->size++;
		}

	return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
	if(this==NULL)
	{
		return -1;
	}
	return addNode(this,this->size,pElement);
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
	Node* pNode=getNode(this, index);

	if(pNode==NULL)
	{
		return NULL;
	}

   return pNode->pElement;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
	Node* auxNode=NULL;
	auxNode=getNode(this, index);
	int returnAux = -1;
	if(this!=NULL && index>=0 && index<ll_len(this)&& auxNode!=NULL)
	{
		auxNode->pElement=pElement;
		returnAux=0;
	}
	return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
	Node* nodoAEliminar= getNode(this, index);
	Node* nodoAnterior=NULL;
	int returnAux = -1;
	if(this!=NULL && index>=0 && index<ll_len(this) && nodoAEliminar!=NULL)
	{
		if (index==0)
		{
			this->pFirstNode=(this->pFirstNode)->pNextNode;
		}else
		{
			nodoAnterior=getNode(this, index-1);
			nodoAnterior->pNextNode=getNode(this, index+1);
		}
		free(nodoAEliminar);
		this->size--;
		returnAux=0;
	}

	return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
	int returnAux = -1;
	int i;
	if(this!=NULL &&!ll_isEmpty(this))
	{
		for(i=0;i <=ll_len(this);i++)
		{
			free(getNode(this, i));
		}
		returnAux=0;
	}

	return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
	int returnAux = -1;

	if(this!=NULL)
	{
	 if(!ll_isEmpty(this))
		{
			ll_clear(this);
			returnAux=0;
		}else
		{
			free(this);
			returnAux=0;
		}
	}

	return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
	int returnAux=-1;
	int i;
	Node* pNode=NULL;
	if(this!=NULL)
	{
		for(i=0;i <ll_len(this);i++)
		{
			pNode=getNode(this, i);
			if(pNode->pElement==pElement)
			{
				returnAux=i;
				break;
			}
		}
	}
	return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
	int returnAux = -1;
	if(this==NULL )
	{
		return returnAux;
	}

	return ll_len(this)==0;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
	return addNode(this,index,pElement);
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
	Node* nodoAEliminar=getNode(this, index);
	void* pElement;

	if(this!=NULL && index>=0 && index<ll_len(this))
	{
		pElement=nodoAEliminar->pElement;
		ll_remove(this,index);
	}else
	{
		return NULL;
	}
    return pElement;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
	int returnAux = -1;
	if(this!=NULL)
	{
		if(ll_indexOf(this, pElement)>-1)
		{
			returnAux=1;
		}else
		{
			returnAux=0;
		}
	}


	return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
	int returnAux = -1;
	void* pElement;
	int i;
	if(this!=NULL && this2!=NULL)
	{
		if(ll_len(this)==ll_len(this2))
		{
			for(i=0; i<=ll_len(this);i++)
			{
				pElement=ll_get(this, i);
				ll_contains(this,pElement);
			}
			returnAux=1;
		}else
		{
			returnAux=0;
		}
	}
	return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    int i;
    void* pElement;

    if(this!=NULL && from>=0 && from<ll_len(this) && to>from && to<=ll_len(this))
    {
    	cloneArray = ll_newLinkedList();
		for(i=from;i<to;i++)
		{
			pElement = ll_get(this,i);
			ll_add(cloneArray,pElement);
		}
    }
    return cloneArray;
}

/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
	LinkedList* this2 = NULL;
	if(this!=NULL)
	{
		this2 = (LinkedList*) malloc(sizeof(LinkedList));
		this2->size=0;
			return this;
	}

	return this2;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
	int i;
	int flagSwap=0;
	void* punteroAElemento;
	void* punteroAElemento2;
	void* elementoAuxiliar;
	int returnAux=-1;

    if(this!=NULL && pFunc !=NULL && (order==1 || order==0))
    {
    	do
		{
			flagSwap = 0;
			for(i=0;i<ll_len(this)-1;i++)
			{
				punteroAElemento = ll_get(this,i);
				punteroAElemento2 = ll_get(this,i+1);

				if((pFunc(punteroAElemento,punteroAElemento2) < 0 && order == 0) ||
					(pFunc(punteroAElemento,punteroAElemento2) > 0 && order == 1))
				{
					elementoAuxiliar = punteroAElemento;
					ll_set(this,i,punteroAElemento2);
					ll_set(this,i+1,elementoAuxiliar);
					flagSwap = 1;
				}
				returnAux = 0;
			}
		}while(flagSwap);
    }

    return returnAux;

}

int ll_filter(LinkedList* this, void (*pFunc)(void*)) /// aplica pfunc a todos los elementos de la lista
{
	Node* pNode=NULL;
	int returnAux=-1;
	if(this!=NULL)
	{
		pNode=this->pFirstNode;
		while(pNode!=NULL)
		{
			pFunc(pNode->pElement);
			pNode=pNode->pNextNode;
		}
		returnAux=0;
	}
	return returnAux;
}
int ll_count(LinkedList* this, int (*fn)(void* element))
{
	Node* pNode=NULL;
	int cantidadDeElementos=0;
	if(this!=NULL)
	{
		pNode=this->pFirstNode;
		while(pNode!=NULL)
		{
			if(fn(pNode->pElement))
			{
				cantidadDeElementos++;
			}
			pNode=pNode->pNextNode;
		}
	}
	return cantidadDeElementos;
}


