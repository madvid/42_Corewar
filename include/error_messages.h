/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_messages.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdavid <mdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 14:58:02 by mdavid            #+#    #+#             */
/*   Updated: 2020/09/03 15:36:15 by mdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MESSAGES_H
# define ERROR_MESSAGES_H

# define FILE_BIG		250

# define NB_ERROR_MSG	27
# define CD_USAGE		0
# define CD_P_STRUCT	1
# define CD_P_IDTAB		2
# define CD_P_OPT		3
# define CD_DUMP 		4
# define CD_VERB		5
# define CD_MUSIC		6
# define CD_UNIQ		7
# define CD_BD_VAL		8
# define CD_BD_FILE		9
# define CD_DUPL_N		10
# define CD_FILE_BIG	11
# define CD_MEM_CHAMP	12
# define CD_EMPTY_CHP	13
# define CD_MAX_CHAMP	14
# define CD_INV_FD		15
# define CD_MAGIC_EXEC	16
# define CD_CHP_SIZ		17
# define CD_CHP_ERR		18
# define CD_SORT_CHP	19
# define CD_PROC_MEM	20
# define CD_CW_STRUCT	21
# define CD_ARENA		22
# define CD_ID_ARENA	23
# define CD_INI_PROC	24
# define CD_FORK		25
# define FIN_DU_GAME	26

# define M_USAGE_1		"Usage: ./corewar [[-dump N1] [-v N2] [-a]]"
# define M_USAGE_2		" [[-n ID] champion1.cor]\n"
# define M_USAGE_3		"     * N1 being an positive integer,\n"
# define M_USAGE_4		"     * N2 being an integer in range [0;31],\n"
# define M_USAGE_5		"     * ID being an integer in range [1;4]."
# define M_USAGE		(M_USAGE_1 M_USAGE_2 M_USAGE_3 M_USAGE_4 M_USAGE_5)
# define M_P_STRUCT		"Error: [Mem. allocation] failed for t_parse *p."
# define M_P_IDTAB		"Error: [Mem. allocation] failed for p->id_available"
# define M_P_OPT		"Error: [Mem. allocation] failed for p->options."
# define M_DUMP_1		"Error: [Dump flag] <-dump nbr_cycles> nbr_cycles need"
# define M_DUMP_2		" to exist and be a positive INT. Only digits also."
# define M_DUMP			(M_DUMP_1 M_DUMP_2)
# define M_VERB			"Error: [Verbose flag] invalid or no parameter."
# define M_MUSIC		"Error: [Music flag] invalid parameter."
# define M_UNIQ			"Error: [Flag] dupplicate option flag."
# define M_BD_VAL_1		"Error: [Number flag] <-n id>, id "
# define M_BD_VAL_2		"must be either 1, 2, 3 or 4."
# define M_BD_VAL		(M_BD_VAL_1 M_BD_VAL_2)
# define M_BD_FILE_1	"Error: either option flag or champion file error.\n"
# define M_BD_FILE_2	"Also, champion file must be of '.cor' extension."
# define M_BD_FILE		(M_BD_FILE_1 M_BD_FILE_2)
# define M_DUPL_N		"Error: [Number flag] <-n id>, repetition of an id."
# define M_FILE_BIG		"Error: champion file name too big."
# define M_MEM_CHAMP_1	"Error: [Mem. allocation] issue during champion"
# define M_MEM_CHAMP_2	" processing."
# define M_MEM_CHAMP	(M_MEM_CHAMP_1 M_MEM_CHAMP_2)
# define M_EMPTY_CHP	"Error: you must precise 1 champion at least."
# define M_MAX_CHAMP	"Error: a maximum of 4 champions is allowed."
# define M_INV_FD		"Error: invalid fd, file or path may not exist."
# define M_MAGIC_EXEC	"Error: COREWAR_EXEC_MAGIC number into file."
# define M_CHP_ERR		"Error: Incorrect bytecode in champion's code."
# define M_SORT_CHP		"Error: Issue during the sorting process of champ list."
# define M_PROC_MEM		"Error: [Mem. allocation] fork/lfork failed to allocate."
# define M_CW_STRUCT	"Error: [Mem. allocation] failed for t_cw *cw."
# define M_ARENA		"Error: [Mem. allocation] failed for cw->arena."
# define M_ID_ARENA		"Error: [Mem. allocation] failed for cw->id_arena."
# define M_INI_PROC		"Error: [Mem. allocation] failed for the initial processes."
# define M_FORK			"Error: [Mem. allocation] failed for a fork/lfork allocation."
# define M_FIN			"FIN DU GAME."

#endif
