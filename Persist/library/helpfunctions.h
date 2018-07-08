char *substring(char *stringIn, int position, int length)
{
	char *pointer;
	int c;

	int _start = 0;
	int _length = 0;

	if (position > strlen(stringIn))
	{
		pointer = (char*)malloc(1);
		*(pointer) = '\0';
	}
	else
	{
		_start = position;
		if ((position + length) > strlen(stringIn))
			_length = strlen(stringIn) - position;
		else
			_length = length;

		pointer = (char*)malloc(_length + 1);


		if (pointer == NULL)
		{
			printf("Unable to allocate memory.\n");
			exit(1);
		}

		for (c = 0; c < _length; c++)
		{
			*(pointer + c) = *(stringIn + position - 1);
			stringIn++;
		}

		*(pointer + c) = '\0';
	}

	return pointer;
}