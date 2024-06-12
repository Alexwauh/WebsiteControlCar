#include "DFRobot_CHfont.h"

DFRobot_CHfont::DFRobot_CHfont()
{
  listhead = NULL;
  gg = &listhead;
}

DFRobot_CHfont::~DFRobot_CHfont()
{
  freelist(gg);
}

void DFRobot_CHfont::freelist(chfont** codehead)
{
  chfont* myhead = NULL;
  if((*codehead) == NULL){
    return;  
  }
  while((*codehead)->next != NULL){
    myhead = (*codehead)->next;
    free((*codehead));
    (*codehead) = myhead;
  }
  if((*codehead) != NULL)
  {
      free((*codehead));
      (*codehead) = NULL;
  }
}

chfont* DFRobot_CHfont::createNew(const ChFont* mycode)
{
  chfont* newcode = (chfont*)malloc(sizeof(chfont));
  newcode->code = mycode;
  newcode->next = NULL;
  return newcode;
}

void DFRobot_CHfont::listAdd(chfont** codehead,const ChFont* mycode)
{
  if(codehead == NULL){
    return;  
  }
  if(*codehead == NULL){
    *codehead = createNew(mycode);
    return;
  }

  chfont* codehead2 = *codehead;
  
  while(codehead2 -> next != NULL) {
    codehead2=codehead2->next;
  }

  codehead2->next = createNew(mycode);
  return;
}


DFRobot_CHfont DFFont;
