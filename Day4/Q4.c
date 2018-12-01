#include <stdio.h>
#include <string.h>

int main()
{
	char *line;
	size_t len;
	int result; 

	char header[100];
	int lineNumber = 0;

	FILE *program;
	program = fopen("my-program.c", "r");

	while(1)
	{
		result = getline(&line, &len, program);
		if (result == -1) break;
		lineNumber++;

		if (line[0] == '#')
		{
			// extract the positions of the header file
			int pos = -1;
			int from = -1, to = -1;
			while(line[++pos])
			{
				if (line[pos] == '>' || (line[pos] == '"' && from != -1))
				{
					to = pos-1;
					break;
				}
				if (line[pos] == '<' || line[pos] == '"')
					from = pos+1;
			}
			memcpy(header, &line[from], to-from+1); 
			header[to-from+1] = '\0';

			break;
		}
	}
	fclose(program);

	// open the header file, and create a new file for pasting
	FILE *head = fopen(header, "r");
	FILE *f = fopen("program.c", "w+");

	// first, append the header file
	while(1)
	{
		result = getline(&line, &len, head);
		if (result == -1) break;
		fprintf(f, "%s", line);
	}
	fclose(head);

	// now, append the program
	program = fopen("my-program.c", "r");
	while(1)
	{
		result = getline(&line, &len, head);
		if (result == -1) break;

		if (line[0] == '#') // don't include the header file
			continue;
		
		fprintf(f, "%s", line);
	}

	fclose(program);
	fclose(f);

	return 0;
}
