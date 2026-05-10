format strings -> printf, scanf
d -> displays an integer in decimal (base 10), where p indicates minimum number of digits to display
e -> displays a floating point number in exponential format, where p indicates how many digits should appear after the decimal point
f -> displays a floating oint number in "fixed decimal" format without an exponent, where p has the same meaning as 'e' identifier
g -> displays a floating point number in 

take the following code for example

int i;
float x;

i = 50;
x = 839.21f;

printf("|%d|%5d|%-5d|%5.3d|\n", i, i, i, i);
printf("|%10.3f|%10.3e|%-10g|\n", x, x, x);
output:
|50|     50|50     |     050|
|   829.210| 8.392e02|839.21    |

%d -> displays i in decimal form, using a minimum amount of space
%5d -> displays i in decimal form, using a minimum of 5 characters
%-5d -> displays i in decimal form, using a minimum of 5 characters since the value of i doesn't require 5 characters, the spaces are added afterward
%5.3d -> displays i in decimal form, using a minimum of 5 characters overall and a minimum of 4 digits. The resulting number of 5 characters (i is right justified)
%10.3f -> displays x in fixed decimal form, using 10 characters overall with 3 digits after the decimal point. Since x requires only seven characters (3 before the decimal point, 3 after the decimal point, and one for the decimal point itself), 3 spaces precede x
%10.3e -> displays x in exponential form, using 10 characters overall, with 3 digits after the decimal point. X requires 9 characters altogether (including the exponent), so 1 space precedes x
%-10.g -> displays x in either fixed decimal form or exponential form using 10 characters overall. in this case printf chose to display x in fixed decimal form. The minus sign forces left justification, so x if followed by 4 spaces

scanf
reads input according to a particular format. 

int i, j;
float x, y;
scanf("%d%d%f%f", &i, &j, &x, &y);

suppose the following line is inputted
1 -20 .3 -4.0e3
- scanf reads the line, converting its characters to the numbers assigned
-1, -20, 0.3, -4000.0
  i,    j  ,   x  ,   y
- scanf "peeks" at the final new-line character without reading it. This new-line will be the first character read by the next scanf call
What output do the following calls of printf produce?
a) printf("%6d,%4d", 86, 1040);
- prints integer 86 with a field of 4 characters wide
- prints integer 1040 with a field of 6 characters wide
b) printf("%12.5e", 30.253);
- prints integer 30.253 in exponential form 12 characters wide with 5 digits after the decimal point
-  3.02530e+01
c) printf("%.4f", 83.162);
- prints floating point 83.162 with 4 integers after the decimal point
- 83.1620
d) printf("%-6.2g", .0000009979)
- prints 1e-0.6
- left aligned, 6 digits minimum (floating point), rounded to 2 sig figs

