/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeharahikaru <maeharahikaru@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 03:37:41 by maeharahika       #+#    #+#             */
/*   Updated: 2023/11/27 04:08:01 by maeharahika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//この関数は、tbl 構造体のメンバである philos 配列の各要素を初期化します。
//philos 配列内の各要素について、インデックスやフォークのポインタなどの値を設定します。また、tbl->philos に philos のポインタを代入します。

void	philo_init(t_table *tbl, pthread_mutex_t *forks, t_philo *philos)
{
	int	i;

	i = 0;
	while (i < tbl->n_philos)
	{
		philos[i].idx = i;
		if (i == 0)
			philos[i].fork_r = &forks[tbl->n_philos - 1]; //最初のフィロソファーの右側のフォークを指定しています。最初のフィロソファーの右側のフォークは、配列の最後の要素に対応しています。
		else
			philos[i].fork_r = &forks[i - 1]; //それ以外のフィロソファーの右側のフォークは、配列の前の要素に対応しています。
		philos[i].fork_l = &forks[i];
		philos[i].tbl = tbl;
		philos[i].last_eat = (int) get_cur_ms() - tbl->start_ms; //最後に食べた時刻をミリ秒単位で取得
		i++;
	}
	tbl->philos = philos;
}

//この関数は、tbl 構造体のメンバであるミューテックスを初期化します。まず、tbl->stop_lock と tbl->waiter のミューテックスを初期化します。
//その後、tbl->forks 配列内の各要素についてもミューテックスを初期化します。もし初期化に失敗した場合は、すべての初期化済みのミューテックスを破棄し、EXIT_FAILURE を返します。

int	mutex_initializer(t_table *tbl)
{
	int	i;

	if (pthread_mutex_init(&tbl->stop_lock, NULL))
		return (EXIT_FAILURE);
	if (pthread_mutex_init(&tbl->waiter, NULL))
	{
		pthread_mutex_destroy(&tbl->stop_lock);
		return (EXIT_FAILURE);
	}
	i = 0;
	while (i < tbl->n_philos)
	{
		if (pthread_mutex_init(&(tbl->forks[i]), NULL))
		{
			pthread_mutex_destroy(&tbl->stop_lock); //初期化に失敗した場合は、すべての初期化済みのミューテックスを破棄し、EXIT_FAILURE を返します。
			pthread_mutex_destroy(&tbl->waiter);
			while (i > 0)
			{
				pthread_mutex_destroy(&tbl->forks[--i]);
			}
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

//この関数は、tbl 構造体のメンバである philos と forks を初期化します。philos は tbl->n_philos 個の要素を持つ領域を確保し、
//forks も同様に確保します。そして、tbl->forks に forks のポインタを代入します。さらに、mutex_initializer 関数を呼び出
//してミューテックスの初期化を行い、philo_init 関数を呼び出して tbl、forks、philos を初期化します。

int	init_philos(t_table *tbl)
{
	t_philo			*philos;
	pthread_mutex_t	*forks;

	philos = ft_calloc(tbl->n_philos, sizeof(t_philo));
	if (!philos)
		return (EXIT_FAILURE);
	forks = ft_calloc(tbl->n_philos, sizeof(pthread_mutex_t));
	if (!forks)
	{
		free (philos);
		return (EXIT_FAILURE);
	}
	tbl->forks = forks;
	if (mutex_initializer(tbl) == EXIT_FAILURE)
	{
		free (philos);
		free (forks);
		return (EXIT_FAILURE);
	}
	philo_init(tbl, forks, philos);
	return (EXIT_SUCCESS);
}

//この関数は、tbl 構造体の各メンバにコマンドライン引数から取得した値を
//設定し、必要な初期化処理を行います。また、エラーチェックも行い、正常
//に初期化が完了した場合は EXIT_SUCCESS を、エラーが発生した場合は EXIT_FAILURE を返します

int	init_handler(t_table *tbl, int argc, char **argv)
{
	bool	to_exit;

	to_exit = false;
	tbl->n_philos = ft_xatoi(argv[1], &to_exit);
	tbl->time_die = ft_xatoi(argv[2], &to_exit);
	tbl->time_eat = ft_xatoi(argv[3], &to_exit);
	tbl->time_slp = ft_xatoi(argv[4], &to_exit);
	if (argc == 6)
		tbl->max_eat = ft_xatoi(argv[5], &to_exit);
	else
		tbl->max_eat = INT_MAX;
	if (to_exit == true)
		return (EXIT_FAILURE);
	tbl->start_ms = get_cur_ms(); //現在の時刻をミリ秒単位で取得
	tbl->to_stop = CONTINUE;
	if (init_philos(tbl) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
