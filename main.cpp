#include <iostream>

//-----------------------------------------------------------------------	
  enum color {BLACK=0, WHITE=1 };
  
  
  struct TPsetColor
  {
  	float x;
  	float y;
  	color color;
  	TPsetColor();
  };
  
  TPsetColor:: TPsetColor()
  {
  	this->x=0;
  	this->y=0;
  	this->color=BLACK;
  }
  
  void TZero(TPsetColor a)
  {
  	a.x=NULL;
  	a.y=NULL;
  }
//-----------------------------------------------------------------------
struct TElem
   {
    
    TPsetColor p;
    TElem *next;
    
    
    TElem();
    ~TElem();
   };
   
   
   
TElem::TElem()
  {
    this->next=NULL;
  }
  
  
  
TElem::~TElem()
  {
    if (this->next !=NULL)
	  {
        delete this->next;
      }
  }
  
  
TElem* NewPoint()
  {
    TElem *pset = new TElem();

    std::cout<<"x="; std::cin>>pset->p.x;
    std::cout<<"y="; std::cin>>pset->p.y;
    char c;
    std::cout<<"color(w or b)="; std::cin>>c;
    if (c=='w') pset->p.color=WHITE;
    if (c =='b') pset->p.color=BLACK;
    
    return pset;
  
  }
  
//-----------------------------------------------------------------------
  struct TTriangle
  {
  	TPsetColor a;
  	TPsetColor b;
  	TPsetColor c;
  	TTriangle *next;
  	~TTriangle();
  	TTriangle(TPsetColor a,TPsetColor b, TPsetColor c);
  };
  
  TTriangle::TTriangle(TPsetColor a,TPsetColor b, TPsetColor c)
  {
  	this->a=a;
  	this->b=b;
  	this->c=c;
  	this->next=NULL;
  	
  }
  
  TTriangle::~TTriangle()
  {
  	this->next=NULL;
  	a.x=NULL;
  	a.y=NULL;
  }
  
  
 
//-----------------------------------------------------------------------

 void  Print(TTriangle *t)
  {
  	std::cout<<"\n ("<<t->a.x<<", "<<t->a.y<<") ";
  	std::cout<<"- ("<<t->b.x<<", "<<t->b.y<<") -";
  	std::cout<<" ("<<t->c.x<<", "<<t->c.y<<")";
  }
  
  int Check(TPsetColor p, TTriangle  *t){
  	float q1 = (t->a.x - p.x)*(t->b.y - t->a.y) - (t->b.x - t->a.x)*(t->a.y - p.y);
  	float q2 = (t->b.x - p.x)*(t->c.y - t->b.y) - (t->c.x - t->b.x)*(t->b.y - p.y);
  	float q3 = (t->c.x - p.x)*(t->a.y - t->c.y) - (t->a.x - t->c.x)*(t->c.y - p.y);
  	if ((q1>0  && q2>0 && q3>0) || (q1<0 && q2<0 && q3<0) ||(q1==0 || q2==0 ||q3==0)) return 1; else return 0;
  	
  	
  }	
  
  TTriangle * deletel(TTriangle*lst, TTriangle *root)
{
    TTriangle *temp;
    if (lst!=root)
    {
    //std::cout<<"\n root!=head";  
       temp = lst;
       while (temp->next != root)
       { 
         temp = temp->next;
       }
       temp->next = root->next;
       delete(root); 
       return(temp);
    }
   else
   {
   	 
   	  if(root->next!=NULL)
		{
	   //std::cout<<"\n root=head, root->next!=0";  
          temp = root->next;
          delete(root); 
          return(temp);  
		}
        else
        {
      //std::cout<<"\n root=head, root->next=0";  
  	  	delete(lst);
	  	return NULL;
        }
   }
}


//------------------------------------------------------------------------
int main(int argc, char** argv) {
	setlocale(LC_ALL,"Rus"); 
	
	TElem *points = NULL;
    char answer;

    while (true)
    {
        std::cout <<"New pset?"; std::cin >>answer;
        if (answer=='y')
		{
            TElem *tmp = NewPoint();
            tmp->next=points;
            points=tmp;
        }
        else
        {
            break;
        }
    
    } 
    	TTriangle *triangle = NULL;
    
    for (TElem*a=points;a!=NULL;a=a->next)
    {
    	for (TElem *b=a->next;b!=NULL;b=b->next)
    	{
    		for (TElem*c=b->next;c!=NULL;c=c->next)
    		{
    			if (a!=b && b!=c && c!=a)
    			{
				
    		 	  if (a->p.color==BLACK && b->p.color==BLACK && c->p.color==BLACK )
			       {
    			  	  if ((c->p.x - a->p.x) / (b->p.x - a->p.x) != (c->p.y - a->p.y ) / (b->p.y- a->p.y) )
					   {
    				      TTriangle *tmp = new TTriangle(a->p,b->p,c->p);
                          tmp->next=triangle;
                          triangle=tmp;
			    	   }
    			   }
    			}
			}
		}
    	
	}
	std::cout<<"\n Вcевозможные черные треугольники";
	for(TTriangle *t=triangle; t!=0;t=t->next)
	{
		Print(t);
	}
	
	TTriangle *tready = triangle;
	 for(TTriangle *trg=triangle; trg!=NULL;trg=trg->next)	 
	 {
	 	for(TElem*pnt=points;pnt!=NULL;pnt=pnt->next)
	 	{
	 		if (pnt->p.color==WHITE) 
	 		{
	 			if (Check(pnt->p,trg)==1)
	 			{
	 				// TTriangle *tmp = new TTriangle(trg->a, trg->b, trg->c);
                      //tmp->next=tready;
                      //tready=tmp;	
					 tready=deletel(tready,trg);
					  
				 }
			 }
	 		
		 }
	 }
	
	
	
	
	
	std::cout<<"\n Ответ";
if (tready!=NULL){
	
	for(TTriangle *t=tready; t!=0;t=t->next)
	{
		Print(t);
	}
}	
else
{
	std::cout<<"\n Черных треугольников, в которых не лежит ни одна белая точка, не существует";
}
	return 0;
}
