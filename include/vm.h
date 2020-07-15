/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 11:52:37 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/15 02:02:15 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

/*
** include de fichiers entête 'externe'
*/
# include <sys/types.h>
# include "../libft/include/libft.h"

#include <stdio.h> // have to be removed at the end

/*
** [SOURCE: op.h]
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
**
** Ci dessous se trouvent la definition des macros du programme de la VM
** La taille des différents types d'éléments dans le fichier binaire (.cor ?).
** Dans le binaire, chaque type occupe un nombre précis de bytes(ici octets):
** type indirect -> 2 bytes, type direct -> 4 bytes, type registre -> 4 bytes.
*/

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE


/*
** This is the definition of the encoding value for a register, a direct
** argument and an indirect. Then It gives us in bits:
**   Register = 01 - Direct = 10 - Indirect = 11
*/

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3


# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4*1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define CMT_CHAR				'#'
# define LBL_CHAR				':'
# define DIR_CHAR				'%'
# define SEP_CHAR				','

# define LBL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"

/*
** Macros relatives au header du code
** NAME_CMD_STRING =	le motif de la commande spécifiant que la string
**						qui suit est le nom du champion
** NAME_CMD_SIZE
** CMT_CMD_STRING
** CMT_CMD_SIZE
*/

# define COREWAR_EXEC_MAGIC		0xea83f3
# define NAME_CMD_STRING		".name"
# define CMT_CMD_STRING			".comment"
# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)

/*
** Le nombre de registre maximum disponible:
*/

# define REG_NUMBER				16

/*
**
**
*/

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

/*
** Macros des auteurs, des structures et prototypes des fonctions
*/

# define BASE					"0123456789abcdef"
typedef struct					s_options
{
	int							dump;
	ssize_t						nbr_cycle;
	int							n;
}								t_options;

typedef struct					s_champ
{
	int							id;
	char						*champ_file;
	char						*name;
	char						*comment;
	int							l_bytecode;
	char						*bytecode;
}								t_champ;


typedef struct					s_parse
{
	int							nb_champ;
	int							id_champ;
	t_options					*options;
	t_list						*t_champ_id;
	char						**error;
}								t_parse;

# define NB_ERROR_MSG			9
# define CD_USAGE				0
# define CD_DUMP 				1
# define CD_BD_VAL				2
# define CD_BD_CHAMP_NB			3
# define CD_MEM_CHAMP			4
# define CD_EMPTY_CHP			5
# define CD_MAX_CHAMP			6
# define CD_BD_CODE				7
# define CD_CHP_ERR				8
# define M_USAGE_1				"Usage: ./corewar [-dump nbr_cycles] "
# define M_USAGE_2				"[[-n number] champion1.cor] ..."
# define M_USAGE				(M_USAGE_1 M_USAGE_2)
# define M_DUMP_1				"Dump error: [-dump nbr_cycles] nbr_cycles need"
# define M_DUMP_2				" to exist, be non null and positive INT."
# define M_DUMP					(M_DUMP_1 M_DUMP_2)
# define M_BD_VAL_1				"value error: [-n number], n "
# define M_BD_VAL_2				"must be either 1, 2, 3 or 4."
# define M_BD_VAL				(M_BD_VAL_1 M_BD_VAL_2)
# define M_BD_CHAMP_NB_1		"Champion file error: file must be a bytecode"
# define M_BD_CHAMP_NB_2		" with '.cor' extension."
# define M_BD_CHAMP_NB			(M_BD_CHAMP_NB_1 M_BD_CHAMP_NB_2)
# define M_MEM_CHAMP_1			"Error: memory allocation issue during parsing"
# define M_MEM_CHAMP_2			" process."
# define M_MEM_CHAMP			(M_MEM_CHAMP_1 M_MEM_CHAMP_2)
# define M_EMPTY_CHP			"Error: You must precise 1 champion at least."
# define M_MAX_CHAMP			"Error: a maximum of 4 champions is allowed."
# define M_BD_CODE				"Error: one of champion's file is not bytecode."
# define M_CHP_ERR				"Error: Incorrect bytecode in champion's code."

/*
** Prototypes des fonctions de parsing des arguments en STDIN
*/

int							vm_parsing(char **av, t_parse *p, t_list **lst_champs);
int							vm_init_parse(t_parse **p);
int							vm_init_parse_error(int code_error, t_parse **p); // print error message if memory allocation issue at initialization
int							vm_error_manager(int code_error, char **error);
int							vm_create_champion(t_list **lst_champs, char *av, t_parse *p);
int 						is_valid_champ_filename(char* filename);
void						vm_print_parsing(t_parse *p); //a retirer
void						vm_print_champ_list(t_list *lst_champs); //a retirer

/*
** Prototypes des fonctions de parsing des fichiers des champions
*/
int							vm_champ_parse(t_list **lst_champs, char **error);
int							get_champ_magic_key(int fd);
char						*get_champ_name(int fd);
char						*get_champ_comment(int fd);
int							get_champ_l_bcode(int fd);
char						*get_champ_bcode(int fd, int l_bcode);

#endif