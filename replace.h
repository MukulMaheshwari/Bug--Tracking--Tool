#include <stdio.h>

/**
 * Returns the length of a string
 **/
int str_len(char* str) {
	int ret = 0;
	while (str[ret]) {
		ret++;
	}
	return ret;
}

/**
 * Replaces all found instances of the passed substring in the passed string.
 *
 * @param search The substring to look for
 * @param replace The substring with which to replace the found substrings
 * @param subject The string in which to look
 *
 * @return A new string with the search/replacement performed
 **/
char* str_replace(char* search, char* replace, char* subject) {
	int i, j, k;
	
	int searchSize = str_len(search);
	int replaceSize = str_len(replace);
	int size = strlen(subject);

	char* ret;

	if (!searchSize) {
		ret = malloc(size + 1);
		for (i = 0; i <= size; i++) {
			ret[i] = subject[i];
		}
		return ret;
	}
	
	int retAllocSize = (str_len(subject) + 1) * 2; // Allocation size of the return string.
    // let the allocation size be twice as that of the subject initially
	ret = malloc(retAllocSize);

	int bufferSize = 0; // Found characters buffer counter
	char* foundBuffer = malloc(searchSize); // Found character bugger
	
	for (i = 0, j = 0; i <= size; i++) {
		/**
         * Double the size of the allocated space if it's possible for us to surpass it
		 **/
		if (retAllocSize <= j + replaceSize) {
			retAllocSize *= 2;
			ret = (char*) realloc(ret, retAllocSize);
		}
		/**
         * If there is a hit in characters of the substring, let's add it to the
         * character buffer
		 **/
		else if (subject[i] == search[bufferSize]) {
			foundBuffer[bufferSize] = subject[i];
			bufferSize++;

			/**
             * If the found character's bugger's counter has reached the searched substring's
             * length, then there's a hit. Let's copy the replace substring's characters
             * onto the return string.
			 **/
			if (bufferSize == searchSize) {
				bufferSize = 0;
				for (k = 0; k < replaceSize; k++) {
					ret[j++] = replace[k];
				}
			}
		}
		/**
         * If the character is a miss, let's put everything back from the buffer
         * to the return string, and set the found character buffer counter to 0.
		 **/
		else {
			for (k = 0; k < bufferSize; k++) {
				ret[j++] = foundBuffer[k];
			}
			bufferSize = 0;
			/**
             * Add the current character in the subject string to the return string.
			 **/
			ret[j++] = subject[i];
		}
	}

	/**
	 * Free memory
	 **/
	free(foundBuffer);
	
	return ret;
}

/*int main(argc, argv) {
	char* origText = "resolved    B802      bug43      12/10/2019      T73000      D73000 ";
	//char* replace = "assigned";
    char* replace1 = "D75000";
	//replace = "XXX";
	char* result = str_replace("D73000", replace1, origText);
    //char* result1 = str_replace("D75000", "D75000", *result);
	printf(result);
    printf("\n");
    
	
	return 0;
}*/



