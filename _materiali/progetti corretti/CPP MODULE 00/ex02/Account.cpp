/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Account.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 20:23:47 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/01/08 20:23:48 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Account.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>

int	Account::_nbAccounts = 0;
int	Account::_totalAmount = 0;
int	Account::_totalNbDeposits = 0;
int	Account::_totalNbWithdrawals = 0;

void	Account::displayAccountsInfos( void ) {

	_displayTimestamp();
	std::cout << "accounts:" << _nbAccounts << ";total:" << _totalAmount << ";deposits:" << _totalNbDeposits << ";withdrawals:" << _totalNbWithdrawals << std::endl;
	return ;
}

void	Account::makeDeposit( int deposit ) {

	_totalAmount += deposit;
	_totalNbDeposits += 1;
	_amount += deposit;
	_nbDeposits += 1;

	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";p_amount:" << _amount - deposit << ";deposit:" << deposit << ";amount:" << _amount << ";deposits:" << _nbDeposits << std::endl;
	return ;
}

bool	Account::makeWithdrawal( int withdrawal ) {

	if (withdrawal > _amount) {
		_displayTimestamp();
		std::cout << "index:" << _accountIndex << ";p_amount:" << _amount + withdrawal << ";withdrawal:refused" << std::endl;
		return false;
	}
	_totalAmount -= withdrawal;
	_totalNbWithdrawals += 1;
	_amount -= withdrawal;
	_nbWithdrawals += 1;

	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";p_amount:" << _amount + withdrawal << ";withdrawal:" << withdrawal << ";amount:" << _amount << ";deposits:" << _nbWithdrawals << std::endl;
	return true;
}

int	Account::checkAmount( void ) const {
	return _amount;
}

void	Account::displayStatus( void ) const {

	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";amount:" << _amount << ";deposits:" << _nbDeposits << ";withdrawals:" << _nbWithdrawals << std::endl;
	return ;
}

void	Account::_displayTimestamp( void ) {

	std::time_t result = std::time(NULL);

	std::cout << std::setfill('0') << "["
				<< 1900 + std::localtime(&result)->tm_year
				<< std::setw(2) << 1 + std::localtime(&result)->tm_mon
				<< std::setw(2) << std::localtime(&result)->tm_mday
				<< "_"
				<< std::setw(2) << std::localtime(&result)->tm_hour
				<< std::setw(2) << std::localtime(&result)->tm_min
				<< std::setw(2) << std::localtime(&result)->tm_sec
				<< "] " << std::flush;
	return ;
}

Account::Account( int initial_deposit ) {

	_nbAccounts += 1;
	_accountIndex = _nbAccounts - 1;
	_amount = initial_deposit;
	_nbDeposits = 0;
	_nbWithdrawals = 0;
	_totalAmount += _amount;

	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";amount:" << initial_deposit << ";created" << std::endl;
	return ;
}

Account::~Account( void ) {

	_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";amount:" << _amount << ";closed" << std::endl;
	return ;
}

int	Account::getNbAccounts( void ) {
	return _nbAccounts;
}

int	Account::getTotalAmount( void ) {
	return _totalAmount;
}

int	Account::getNbDeposits( void ) {
	return _totalNbDeposits;
}

int	Account::getNbWithdrawals( void ) {
	return _totalNbWithdrawals;
}
