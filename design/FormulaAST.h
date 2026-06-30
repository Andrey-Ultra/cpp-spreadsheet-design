#pragma once

#include "FormulaLexer.h"
#include "common.h"

#include <forward_list>
#include <functional>
#include <stdexcept>

namespace ASTImpl {
class Expr;
}

class ParsingError : public std::runtime_error {
    using std::runtime_error::runtime_error;
};

class FormulaAST {
public:
    explicit FormulaAST(std::unique_ptr<ASTImpl::Expr> root_expr,
                        std::forward_list<Position> cells);
    FormulaAST(FormulaAST&&) = default;
    FormulaAST& operator=(FormulaAST&&) = default;
    ~FormulaAST();

    double Execute(const SheetInterface& sheet) const;
    //вычисляю результат в ячейке Если дойду до узла с позицией то вызову
    // sheet.GetCell(A1)->GetValue() именно поэтому sheet передаётся что бы обращатся к ячейкам

    std::forward_list<Position>& GetCells();

    void Print(std::ostream& out) const;
    void PrintFormula(std::ostream& out) const;

private:
    std::unique_ptr<ASTImpl::Expr> root_expr_;
    // спиок позиций ячеек встреченных при парсинге нужен для GetReferencedCells() в  Formula и cell
    std::forward_list<Position> cells_;
};

FormulaAST ParseFormulaAST(std::istream& in);
FormulaAST ParseFormulaAST(const std::string& in_str);
