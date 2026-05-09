format strings -> printf, scanf
take the following code for example

int i;
i = 50;
printf("|%d|%5d|%-5d|%5.3d|\n", i, i, i, i);

output:
|50|     50|50     |     050|

%d -> displays i in decimal form, using a minimum amount of space
%5d -> displays i in decimal form, using a minimum of 5 characters
%-5d -> displays i in decimal form, using a minimum of 5 characters since the value of i doesn't require 5 characters, the spaces are added afterward
%5.3d -> displays i in decimal form, using a minimum of 5 characters overall and a minimum of 4 digits. The resulting number of 5 characters (i is right justified)
%10.
