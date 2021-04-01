#include <stdio.h>
#include "lirc.h"

int m,a[10];

int main () {

	for (int n=1; n!=11; n++) { 
	rand(a[n]);
	}
	bubble_sort(m,a);
	for (int n=1; n!=11; n++) { 
	printf("%d",a[n]);
	}

}