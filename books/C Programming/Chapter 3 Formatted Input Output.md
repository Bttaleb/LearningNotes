format strings -> printf, scanf
take the following code for example

int i;
float x;

i = 50;
x = 839.21f;

printf("|%d|%5d|%-5d|%5.3d|\n", i, i, i, i);
printf("|%10.3f|%10.3e|%-10g|\n", x, x, x);
output:
|50|     50|50     |     050|
|   829.210| 8.392e02|839.21

%d -> displays i in decimal form, using a minimum amount of space
%5d -> displays i in decimal form, using a minimum of 5 characters
%-5d -> displays i in decimal form, using a minimum of 5 characters since the value of i doesn't require 5 characters, the spaces are added afterward
%5.3d -> displays i in decimal form, using a minimum of 5 characters overall and a minimum of 4 digits. The resulting number of 5 characters (i is right justified)
%10.3f -> displays x in fixed decimal form, using 10 characters overall with 3 digits after the decimal point. Since x requires only seven characters (3 before the decimal point, 3 after the decimal point, and one for the decimal point itself), 3 spaces precede x
%10.3e -> displays x in exponential form, using 10 characters overall, with 3 digits after the decimal point. X requires 9 characters altogether (including the exponent), so 1 space precedes x
%10.
