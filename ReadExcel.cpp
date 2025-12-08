#include <iostream>
#include <vector>
#include <string>
#include <OpenXLSX.hpp> // OpenXLSXライブラリのヘッダー

// OpenXLSXライブラリのセットアップ方法:
// 1. GitHubからOpenXLSXをクローンまたはダウンロードします: https://github.com/troldal/OpenXLSX
// 2. プロジェクトにOpenXLSXをビルドしてリンクします。
//    CMakeを使用している場合、OpenXLSXのCMakeLists.txtをプロジェクトに追加し、
//    target_link_librariesでリンクします。
//    例:
//    add_subdirectory(path/to/OpenXLSX)
//    target_link_libraries(YourProjectName OpenXLSX)
// 3. Visual Studioを使用している場合、OpenXLSXのソースファイルをプロジェクトに追加するか、
//    ビルド済みのライブラリをリンクします。インクルードディレクトリにOpenXLSXのヘッダーパスを追加してください。

/**
 * @brief Excelファイルから指定されたシートのデータを2次元std::vector<std::string>として読み込みます。
 * @param filePath Excelファイルのパス。
 * @param sheetName 読み込むシートの名前。
 * @return 読み込まれたデータを含む2次元ベクトル。エラーが発生した場合は空のベクトルを返します。
 */
std::vector<std::vector<std::string>> readExcelSheetToVector(
    const std::string& filePath,
    const std::string& sheetName)
{
    std::vector<std::vector<std::string>> data;
    std::string filePath = R"(//192.168.1.247/共有/技術課ﾌｫﾙﾀﾞ/品質検査/小糸B試験管理ｼｰﾄ.xlsx)";

    try {
        // Excelファイルを開く
        OpenXLSX::XLDocument doc;
        doc.open(filePath);

        // 指定されたシートを選択
        OpenXLSX::XLWorkbook workbook = doc.workbook();
        if (!workbook.sheetExists(sheetName)) {
            std::cerr << "エラー: シート '" << sheetName << "' がファイル '" << filePath << "' に見つかりません。" << std::endl;
            doc.close();
            return data; // 空のデータを返す
        }
        OpenXLSX::XLWorksheet sheet = workbook.worksheet("hinbantaiou");

        // シートの行と列を反復処理してデータを読み込む
        // OpenXLSXは1ベースのインデックスを使用します
        for (auto& row : sheet.rows()) {
            std::vector<std::string> rowData;
            for (auto& cell : row.cells()) {
                // セルの値を文字列として取得
                rowData.push_back(cell.value().asString());
            }
            data.push_back(rowData);
        }

        doc.close();
    } catch (const OpenXLSX::XLception& e) {
        std::cerr << "OpenXLSXエラー: " << e.what() << std::endl;
        return {}; // エラー時は空のベクトルを返す
    } catch (const std::exception& e) {
        std::cerr << "一般的なエラー: " << e.what() << std::endl;
        return {}; // エラー時は空のベクトルを返す
    }

    return data;
}

int main() {
    // 使用例
    std::string excelFilePath = "example.xlsx"; // 実際のExcelファイルパスに置き換えてください
    std::string targetSheetName = "Sheet1";     // 実際のシート名に置き換えてください

    // テスト用のダミーExcelファイルを作成 (OpenXLSXが動作することを確認するため)
    try {
        OpenXLSX::XLDocument doc;
        doc.create(excelFilePath);
        OpenXLSX::XLWorkbook workbook = doc.workbook();
        workbook.addWorksheet(targetSheetName);
        OpenXLSX::XLWorksheet sheet = workbook.worksheet(targetSheetName);

        sheet.cell("A1").value() = "Header1";
        sheet.cell("B1").value() = "Header2";
        sheet.cell("A2").value() = "Data1A";
        sheet.cell("B2").value() = "Data1B";
        sheet.cell("A3").value() = "Data2A";
        sheet.cell("B3").value() = "Data2B";
        sheet.cell("C2").value() = "Data1C"; // C列にもデータ追加

        doc.save();
        doc.close();
        std::cout << "テスト用Excelファイル '" << excelFilePath << "' を作成しました。" << std::endl;
    } catch (const OpenXLSX::XLception& e) {
        std::cerr << "テスト用Excelファイル作成中にOpenXLSXエラー: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "テスト用Excelファイル作成中に一般的なエラー: " << e.what() << std::endl;
        return 1;
    }


    std::vector<std::vector<std::string>> excelData = readExcelSheetToVector(excelFilePath, targetSheetName);

    if (!excelData.empty()) {
        std::cout << "\nExcelデータの内容:" << std::endl;
        for (const auto& row : excelData) {
            for (const auto& cellValue : row) {
                std::cout << cellValue << "\t";
            }
            std::cout << std::endl;
        }
    } else {
        std::cout << "Excelデータの読み込みに失敗したか、データが空です。" << std::endl;
    }

    return 0;
}
