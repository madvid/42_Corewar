/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2020/07/15 15:10:43 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#define IND_SIZE				2
#define REG_SIZE				4
#define DIR_SIZE				REG_SIZE

/*
** This is the definition of the encoding value for a register, a direct
** argument and an indirect. Then It gives us in bits:
**   Register = 01 - Direct = 10 - Indirect = 11
*/

# define REG_CODE				1
# define IND_CODE				3
# define DIR_CODE				2

/*
** Macro related to parsing part of corewar(=vm): max players authorized.
*/

#define MAX_PLAYERS				4

/*
** Macro related to parsing part of asm: max arguments authorized for opcode.
*/

#define MAX_ARGS_NUMBER			4

/*
** Macros related to construction, manipulation and positionning of champions
*/

#define MEM_SIZE				(4*1024)
#define IDX_MOD					(MEM_SIZE / 8)
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

/*
** Macros related to the asm part.
*/

#define COMMENT_CHAR			'#'
#define LABEL_CHAR				':'
#define DIRECT_CHAR				'%'
#define SEPARATOR_CHAR			','
#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"
#define NAME_CMD_STRING			".name"
#define COMMENT_CMD_STRING		".comment"

/*
** Maximum registers available for each (?) champions.
*/

#define REG_NUMBER				16

/*
** Macros related to the processes run globally.
*/

#define CYCLE_TO_DIE			1536
#define CYCLE_DELTA				50
#define NBR_LIVE				21
#define MAX_CHECKS				10

typedef char	t_arg_type;

/*
** ?
*/

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

/*
** Macros related to the size of name and comment + the magic key which must
** be present at the beginning of '.cor' files.
*/

# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct		header_s
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}					header_t;
