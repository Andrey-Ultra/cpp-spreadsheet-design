#pragma once

#include "cell.h"
#include "common.h"

#include <map>
#include <memory>
#include <ostream>
#include <set>

class Sheet : public SheetInterface {
public:
    ~Sheet();

    void SetCell(Position pos, std::string text) override;
    // Пример работы
    /*
     * 1) нпаример вызвали SetCell("C1", "=A1+B2")
     * 2) парсим Formula содержит AST и cells_ = {A1, B2}
     * 3) проверим есть ли цикл  HasCycle(C1, {A1, B2}) если встретим С1 то бром=сим исколючение
     * 4) Снимае старые обратные рёбра для каждой существующей до этого зависмости
     * 5) Обновляем ячейку С1
     *  6) Ставим нровые обратные рёбра A1->dependents_.insert(C1_ptr) и для В2
     *  7) InvalidateDependents(C1) сбрасываем кэш у C1 и для всех кто от него зависел!
     */

    const CellInterface* GetCell(Position pos) const override;
    CellInterface* GetCell(Position pos) override;

    void ClearCell(Position pos) override;

    Size GetPrintableSize() const override;

    void PrintValues(std::ostream& output) const override;
    void PrintTexts(std::ostream& output) const override;

private:
    // вспомогательный метод для создания ячеек
    Cell* GetOrCreateCell(Position pos);
    // проверка на создание цикла
    // реализую как обход в глубину
    bool HasCycle(Position pos, const std::vector<Position>& new_deps) const;
    // инвалидипует все зависимые яейки от данной
    void InvalidateDependents(Cell* cell);

    std::map<Position, std::unique_ptr<Cell>> cells_;
    std::multiset<int> rows_;
    std::multiset<int> cols_;
};
