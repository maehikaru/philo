/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maeharahikaru <maeharahikaru@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 03:38:14 by maeharahika       #+#    #+#             */
/*   Updated: 2023/11/27 04:48:32 by maeharahika      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	to_continue(t_table *tbl)
{
	pthread_mutex_lock(&tbl->stop_lock);
	if (tbl->to_stop != CONTINUE)
	{
		pthread_mutex_unlock(&tbl->stop_lock);
		return (false);
	}
	else
	{
		pthread_mutex_unlock(&tbl->stop_lock);
		return (true);
	}
}


//この関数は、フィロソファーが食事をするために必要なフォークを取得し、食事を行います。また、食事の開始時間を記録し、一定時間のスリープ後にフォークを解放します。

void	philo_eat(t_philo *philo, t_table *tbl)
{
	pthread_mutex_lock(philo->fork_r);
	ft_xprintf(philo->idx, "has taken a fork", tbl);
	if (tbl->n_philos == 1) //フィロソファーの数が1人の場合、処理を終了してNULLを返します
	{
		ft_xusleep(tbl->time_eat);
		return ;
	}
	pthread_mutex_lock(philo->fork_l);
	ft_xprintf(philo->idx, "has taken a fork", tbl);
	pthread_mutex_lock(&tbl->waiter);
	ft_xprintf(philo->idx, "is eating", tbl);
	philo->last_eat = get_cur_ms() - tbl->start_ms;
	pthread_mutex_unlock(&tbl->waiter);
	ft_xusleep(tbl->time_eat);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(philo->fork_l);
}

void	philo_sleep_and_think(t_philo *philo, t_table *tbl)
{
	ft_xprintf(philo->idx, "is sleeping", tbl);
	ft_xusleep(tbl->time_slp);
	ft_xprintf(philo->idx, "is thinking", tbl);
}

void *philo_thread(void *arg) //フィロソファーのスレッドのエントリーポイントとなる関数
{
    t_philo *philo;
    t_table *tbl;
    int i;

    philo = (t_philo *)arg; //arg を t_philo 型のポインタとしてキャストし、その結果を philo に代入する操作
    tbl = philo->tbl;

    // フィロソファーのインデックスが偶数でない場合、一定時間スリープします
    if (philo->idx % 2 != 0)
        ft_xusleep(tbl->time_eat / 10);

    i = 0;
    while (to_continue(tbl))
    {
        // フィロソファーが食事をします
        philo_eat(philo, tbl);

        // フィロソファーの数が1人の場合、処理を終了してNULLを返します
        if (tbl->n_philos == 1)
            return NULL;

        // 最大食事回数に達した場合、処理を終了してNULLを返します
        if (i >= tbl->max_eat)
        {
            pthread_mutex_lock(&tbl->stop_lock);
            tbl->to_stop = FINISHED;
            pthread_mutex_unlock(&tbl->stop_lock);
            return NULL;
        }

        // フィロソファーが休息し、考え事をします
        philo_sleep_and_think(philo, tbl);

        i++;
    }

    return NULL;
}

//この関数は、フィロソファーのスレッドを作成し、監視スレッドを開始するために使用されます。

void	thread_handler(t_table *tbl)
{
	int		i;

	i = 0;
	while (i < tbl->n_philos)
	{
		pthread_create(&(tbl->philos[i].tid), NULL, \
					philo_thread, (void *)&tbl->philos[i]);
		//start_routine = philo_thread: スレッドのエントリーポイントとなる関数へのポインタを指定します。この関数はスレッドが開始されると実行されます。
		i++;
	}
	thread_monitor(tbl);
}
