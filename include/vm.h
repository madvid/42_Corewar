/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 11:52:37 by mdavid            #+#    #+#             */
/*   Updated: 2020/07/07 15:53:53 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

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


# define MAX_ARGS_NUMBER			4
# define MAX_PLAYERS				4
# define MEM_SIZE				(4*1024)
# define IDX_MOD					(MEM_SIZE / 8)
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
# define CYCLE_DELTA				50
# define NBR_LIVE				21
# define MAX_CHECKS				10

#endif