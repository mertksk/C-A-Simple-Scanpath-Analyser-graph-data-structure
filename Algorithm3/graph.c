#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

void insertionSort(float arr[], int n)  /// sort alghoritm to descendend print
{ 
	int i, key, j; 
	for (i = 1; i < n; i++) { 
		key = arr[i]; 
		j = i - 1; 

		while (j >= 0 && arr[j] < key) { 
			arr[j + 1] = arr[j]; 
			j = j - 1; 
		} 
		arr[j + 1] = key; 
	} 
} 



int lengthFinder(char a[]){ // finds the length of an string array
 		int counter=0;
 		while(a[counter]!='\0'){
 			counter++;
		 }
		 return counter;
	 }

//parts of edit Distance alghortim
int min(int x, int y, int z) { 
	 if(x < y) {
      if(x < z)
         return x;
      else
         return z;
   }else {
      if(y < z)
         return y;
      else
         return z;
   }
}
//Edit distance alghorithm which returns the difference between series
int editDist(char str1[], char str2[], int m, int n){

	
	if (m == 0)
		return n;

	
	if (n == 0)
		return m;


	if (str1[m - 1] == str2[n - 1])
		return editDist(str1, str2, m - 1, n - 1);

	return 1
		+ min(editDist(str1, str2, m, n - 1), 
				editDist(str1, str2, m - 1, n), 
				editDist(str1, str2, m - 1,n - 1) 
			);
}
struct graphHead{
	int count;  // number of vertices
	struct graphVertex *first; 
};

struct graphVertex{
	struct graphVertex *next;
	int mainDigit; //title
	char inData[50]; //Paths
	int inDegree; 
	int outDegree;
	int processed; //Can be used a flag, such as visited or unvisited in traversal
	struct graphArc *firstArc;
};

struct graphArc{ //Arch definition
	struct graphVertex *destination; //Holded location
	struct graphArc *next; // next arc
	
};

struct graphHead * createGraph(void){ //Creates empty graph
	struct graphHead *head = (struct graphHead *)malloc(sizeof(struct graphHead));
	head->count = 0;
	head->first = NULL;
	return head;
}


// printer function for our graps and vertices
void printSimilarScanpaths(struct graphHead * head){
	struct graphVertex *tempVertex = NULL;
	struct graphArc * tempArc = NULL;
	
	int counter=0;
	tempVertex = head->first;
	while(tempVertex != NULL){
		counter++;
		printf("\nVertex %d: %d -> ",counter, tempVertex->mainDigit);
		tempArc = tempVertex->firstArc;
		while(tempArc != NULL){	
			printf("%dth Vertex -> ", tempArc->destination->mainDigit);		
			tempArc = tempArc->next;
		}
		printf("\n");
		tempVertex = tempVertex->next;
	}
}



int createEdges(struct graphHead *head,int size){
	//, int fromKey, int toKey will be implemented
	int temporary=(size*size)-5;
	float *descending=(float*)malloc(temporary*sizeof(float)); // dynamic float array
	float S;
	int difference,temp;
	struct graphVertex *tempVertex = NULL; 
	tempVertex = head->first;
	int length1,length2;
	char hold[50][50] ;
	// dynamic two dimensional integer array
	int len=0 ; 
	int *ptr, **arr; 
	int count = 0,i,j; 
	len = sizeof(int *) * size + sizeof(int) * size * size; 
	arr = (int **)malloc(len); 
	ptr = (int *)(arr + size); 
	for(i = 0; i < size; i++) 
		arr[i] = (ptr + size * i); 
		
	for (i = 0; i < size; i++) 
		for (j = 0; j < size; j++) 	arr[i][j] = 0; 

	count=0;
	int indexer=0;
	
	while(tempVertex != NULL){
	
		strcpy(hold[count],tempVertex->inData);
		tempVertex = tempVertex->next;
		count++;
		}
		//DIFFERENCE FINDING THROUGH DIFFERENCE ALGORITHM
	int count2;
	for(count=0;count<size;count++){ 

		for(count2=0;count2<size;count2++){
			if(count!=count2){
		
		
			length1=lengthFinder(hold[count]);
			length2=lengthFinder(hold[count2]);
			
			difference=editDist(hold[count],hold[count2],length1,length2);
			if(length1<length2) length1=length2;
			S = (100*(1 - (difference /(float)length1)));
			if(indexer==temporary)indexer=0;
			if(count>count2){
				descending[indexer]=S;
			}
			indexer++;
		
			arr[count][count2]=S;
			
		 
			
			
			
	
		}	}
	}
	
	
	//sending insertion to make it descending
	insertionSort(descending,temporary);

  for(indexer=0;indexer<temporary;indexer++){
	for(count=0;count<size;count++){
		for(count2=0;count2<size;count2++){
			 	
				 if(descending[indexer]==arr[count][count2] & (count!=count2)){
				 	if(count>count2){
					 
			 		printf("\nSimilarity Score between %d and %d : %.2f -->",count+1,count2+1,descending[indexer] );
				 }}
			 
			 }
		
		}}
	
	////adds edges to our vertexes
	for(count=0;count<size;count++){
		for(count2=0;count2<size;count2++){
			if(arr[count][count2]>=50){
				
				struct graphArc *arc = (struct graphArc *) malloc(sizeof(struct graphArc));
				struct graphVertex *fromVertex = NULL, *toVertex = NULL;
					
				struct graphArc *tempArc = NULL;
				fromVertex = head->first;
					
				while(fromVertex != NULL && fromVertex->mainDigit != count+1)
					fromVertex = fromVertex->next;
		
				if (fromVertex ==NULL)
					continue; //fromKey Not found
				
				toVertex = head->first;
				while(toVertex != NULL && toVertex->mainDigit != count2+1)
					toVertex = toVertex->next;
				
				if (toVertex ==NULL)
					continue; //toKey Not found
				
				fromVertex->outDegree++;
				toVertex->inDegree++;
				
				arc->destination = toVertex;
				
				tempArc = fromVertex->firstArc;
				if (tempArc == NULL){
					fromVertex->firstArc = arc;
					arc->next = NULL;
					//dd
					
					continue;
				}
				else{
					while(tempArc->next != NULL){
						tempArc = tempArc->next;
					}
				
					tempArc->next = arc;
					arc->next= NULL;
					
					
					continue;
		}
				
				
				
			}
		}
	}
	
	
	

}






struct graphHead * createVertices(char path[],int *size){//creates vertices 
	struct graphHead *head=createGraph();// created an empty graph
	int verticeCounter=0;
	FILE *file;
	file = fopen(path, "r");
	char a[50];
	char data[50][50];
  
  //Initial loads of File
	printf("DATAS TAKEN FROM THE FILE!");
	printf("\n\n-----------------------\n");
	while(!feof(file)){
		
		fscanf (file, "%s",data[verticeCounter]);			
		verticeCounter++;  
	}

	fclose(file);		//close the file
	verticeCounter--;
	int cnt;
	for(cnt=0;cnt<verticeCounter;cnt++)printf("\nData from File for Vertex %d: %s",cnt+1,data[cnt]);
	//Vertex addition
	int count;
	for(count=0;count<verticeCounter;count++){
	
		struct graphVertex *vertex = (struct graphVertex *)malloc(sizeof(struct graphVertex));
		vertex->next = NULL;
		vertex->mainDigit = count+1;
		
		char dummy[50];
		strcpy(dummy,data[count]);
		strcpy(vertex->inData,dummy);	
		
		vertex->inDegree = 0;
		vertex->outDegree = 0;
		vertex->firstArc = NULL;
		head->count++;
	
	if(head->first == NULL){
		head->first = vertex;
		}
	else{
		struct graphVertex *temp = head->first;
		while(temp->next != NULL){
			temp = temp->next;
		}
		temp->next = vertex;

	
	}}

	*size=verticeCounter;
	return head;
}//







//Testing purposes!
int main(){
	char path[50];
	printf("Enter a file name >");
	scanf("%s",path);
	int size=0; // initial size
	struct graphHead *head = createVertices(path,&size); // calls createVertices
	//printf("Sizer 1. %d",size);	
	printf("\nVertices are created!\n");
	createEdges(head, size);; // creates edge
	printf("Edges are created!\n");
	printSimilarScanpaths(head);

	
	
	return 0;
}



