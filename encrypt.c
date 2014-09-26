
#include "encrypt.h"

#define ALL_MAX_PATH MAX_PATH + MAX_PATH + MAX_PATH + MAX_PATH
#define FREE_ALL free(temporary_a); free(temporary_b); free(temporary_c); free(temporary_d)
#define VALIDA_STR_A(STR, VALOR) if (!(strlen(STR) >= VALOR)) { FREE_ALL; return result; }
#define VALIDA_STR_B(STR, VALOR) if (!(strlen(STR) == VALOR)) { FREE_ALL; return result; }

#define FORMAT_NUMBER(STROUT) for (a = 0; STROUT[a] != '\0'; a++) {                        \
   if (a == 4)  { temporary_a[a] = '\0'; for (b = 0; STROUT[a] != '\0'; b++, a++)          \
   STROUT[b] = STROUT[a]; STROUT[b] = '\0'; } temporary_a[a] = STROUT[a]; }                \
   _strrev(STROUT); if (STROUT[0] == '0') STROUT[0] = '1'                                  \

#define GENERATE(A, B, C, D, E, F) if (global_key % 2 == 0) {                              \
   if (a % 2 == 0) temporary_d[a] = A; else { if (b % 2 == 0) temporary_d[a] = B;          \
   else temporary_d[a] = C; } } else { if (d % 2 == 0) temporary_d[a] = D;                 \
   else { if (c % 2 == 0) temporary_d[a] = E; else temporary_d[a] = F; } }                 \

int encrypt (char * string)
{
   char * temporary_a, * temporary_b, * temporary_c, * temporary_d;
   int a, b, c, d;
   int key_temp, global_key, rand_key;
   int result = CRYPTOX_ERROR;

   if ((temporary_a = (char *)malloc(ALL_MAX_PATH)) == NULL) return result;
   if ((temporary_b = (char *)malloc(ALL_MAX_PATH)) == NULL) return result;
   if ((temporary_c = (char *)malloc(ALL_MAX_PATH)) == NULL) return result;
   if ((temporary_d = (char *)malloc(ALL_MAX_PATH)) == NULL) return result;

   memset(temporary_a, 0x00, ALL_MAX_PATH);
   memset(temporary_b, 0x00, ALL_MAX_PATH);
   memset(temporary_c, 0x00, ALL_MAX_PATH);
   memset(temporary_d, 0x00, ALL_MAX_PATH);

   // Gera chave randomica...
   key_temp = (int)GetTickCount() * 5;
   sprintf(temporary_a, "%d", key_temp);

   VALIDA_STR_A(temporary_a, 8) for (a = 0; a != 8; a++) temporary_b[a] = temporary_a[a];
   VALIDA_STR_B(temporary_b, 8) memset(temporary_a, 0x00, ALL_MAX_PATH);
   FORMAT_NUMBER(temporary_b);

   memset(temporary_a, 0x00, ALL_MAX_PATH);

   key_temp = (int)GetTickCount() * key_temp;
   sprintf(temporary_a, "%d", key_temp);

   VALIDA_STR_A(temporary_a, 8) for (a = 0; a != 8; a++) temporary_c[a] = temporary_a[a];
   VALIDA_STR_B(temporary_c, 8) memset(temporary_a, 0x00, ALL_MAX_PATH);
   FORMAT_NUMBER(temporary_c);

   sprintf(temporary_d, "%s%s", temporary_b, temporary_c);
   VALIDA_STR_B(temporary_d, 8)
   
   global_key = (int)strtol(temporary_d, (char **)0, 10); 
   rand_key = global_key;

   // Encoda string...
   memset(temporary_a, 0x00, ALL_MAX_PATH);
   memset(temporary_b, 0x00, ALL_MAX_PATH);

   for (a = 0; string[a]; a++) 
   {
      if (string[a] > rand_key) 
      {
         b = string[a] - rand_key;
         rand_key = rand_key + b;

         sprintf(temporary_a, "D%d", b);
         strcat(temporary_b, temporary_a);
      }

      if (string[a] < rand_key) 
      {
         b = rand_key - string[a];
         rand_key = rand_key - b;

         sprintf(temporary_a, "M%d", b);
         strcat(temporary_b, temporary_a);
      }

      if (string[a] == string[a+1]) 
      {
         sprintf(temporary_a, "R%d", b);
         strcat(temporary_b, temporary_a);
      }
   }

   // Monta string...
   memset(temporary_a, 0x00, ALL_MAX_PATH);
   memset(temporary_c, 0x00, ALL_MAX_PATH);
   sprintf(temporary_a, "%d", global_key);

   for (a = 0; temporary_a[a] != '\0'; a++)
   {
      if (a == 4)
      {
         temporary_c[a] = '\0';
         for (b = 0; temporary_a[a] != '\0'; b++, a++)
         {
            temporary_a[b] = temporary_a[a];
         }
         temporary_a[b] = '\0';
      }
      temporary_c[a] = temporary_a[a];
   }

   VALIDA_STR_B(temporary_a, 4)
   VALIDA_STR_B(temporary_c, 4)

   sprintf(temporary_d, "%s%s%s", temporary_a, temporary_b, temporary_c);

   // Ofusca string...
   for (a = 0; temporary_d[a] != '\0' ; a++)
   {
      b = (int)temporary_d[a];
      c = global_key / 3;
      d = b + c;

      switch (temporary_d[a]) 
      {
      case 'D': GENERATE('A', 'D', 'a', 'n', '}', ';') break;
      case 'M': GENERATE('E', 'H', 'o', 'p', '@', '.') break;
      case 'R': GENERATE('I', 'R', 'z', 'f', '&', ',') break;
      case '0': GENERATE('B', 'K', 'j', 'k', '#', ':') break;
      case '1': GENERATE('F', 'S', 'q', 't', ')', '^') break;
      case '2': GENERATE('L', 'M', 'e', 'y', '-', '_') break;
      case '3': GENERATE('O', 'U', 'r', 'b', '*', '?') break;
      case '4': GENERATE('Q', 'T', 'i', 's', '%', '/') break;
      case '5': GENERATE('J', 'Y', 'm', 'l', '$', '>') break;
      case '6': GENERATE('C', 'N', 'u', 'v', '(', '[') break;
      case '7': GENERATE('W', 'V', 'c', 'd', '+', '!') break;
      case '8': GENERATE('G', 'P', 'w', 'x', '{', '~') break;
      case '9': GENERATE('X', 'Z', 'g', 'h', '=', '<') break;
      }
   }

   strcpy(string, temporary_d);

   free(temporary_a);
   free(temporary_b);
   free(temporary_c);
   free(temporary_d);
   return CRYPTOX_ERROR_SUCCESS;
}
