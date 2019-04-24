#include <unistd.h>
int main()
{
 	unlink("victim.txt");
	return 0;
}
