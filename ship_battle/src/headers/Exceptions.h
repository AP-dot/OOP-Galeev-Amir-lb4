#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>


class GameException : public std::exception {
public:
    explicit GameException(const std::string& message) : message(message) {}

    virtual const char* what() const noexcept override {
        return message.c_str();
    }

protected:
    std::string message;
};

class NoAbilitiesException : public GameException {
public:
    NoAbilitiesException() : GameException("Нет доступных способностей для применения.") {}
};

class OverlappingShipsException : public GameException {
public:
    OverlappingShipsException() : GameException("Корабли не могут пересекаться или располагаться вплотную.") {}
};

class OutOfBoundsAttackException : public GameException {
public:
    OutOfBoundsAttackException() : GameException("Атака выходит за границы игрового поля.") {}
};

class OutOfShipLen : public GameException {
public:
    OutOfShipLen() : GameException("Атака выходит за длину корабля.") {}
};

class AlreadyDestroyed : public GameException {
public:
    AlreadyDestroyed() : GameException("Корабль уже уничтожен.") {}
};


class InvalidInputType : public GameException {
public:
    InvalidInputType() : GameException("Error: Incorrect input type") {}
};


class NegativeNumberEntering : public GameException {
public:
    NegativeNumberEntering() : GameException("Error: Entering number must be positive") {}
};

class InvalidCoordinatesFormat : public GameException {
public:
    InvalidCoordinatesFormat() : GameException("Error: Expected two numbers separated by a space") {}
};


#endif