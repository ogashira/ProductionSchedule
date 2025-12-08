#include "Excel.h"
#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <OpenXLSX/OpenXLSX.hpp> // Header for the OpenXLSX library
#include "StringUtils.h" // Include for string conversion utilities

// Note on setting up the OpenXLSX library:
// 1. Clone or download OpenXLSX from GitHub: https://github.com/troldal/OpenXLSX
// 2. Build and link OpenXLSX in your project.
//    - If using CMake, add OpenXLSX to your CMakeLists.txt project and link it.
//    - If using Visual Studio, add the OpenXLSX source files to your project or link against the built library.
//      Ensure the include directories are set up correctly.

/**
 * @brief Reads data from a specified sheet in an Excel file into a 2D vector of strings.
 * @param data A pointer to a 2D vector where the read data will be stored.
 */
void Excel::readExcelHinbantaiouToVec( std::vector<std::vector<std::string>>* data)
{
    const std::string sheetName = "hinbantaiou";
    // The file path contains Japanese characters. Since the source file is CP932,
    // this string literal will be correctly encoded as CP932.
    std::string filePath_cp932 = 
                "//192.168.1.247/ã§óL/ãZèpâ€Ã´Ÿ¿ﬁ/ïiéøåüç∏/è¨éÖBééå±ä«óùº∞ƒ.xlsx";

    try {
        // OpenXLSX expects a UTF-8 encoded path. Convert the CP932 path to UTF-8.
        std::string filePath_utf8 = Cp932ToUtf8(filePath_cp932);

        // Open the Excel file
        OpenXLSX::XLDocument doc;
        doc.open(filePath_utf8);

        // Select the specified sheet
        OpenXLSX::XLWorkbook workbook = doc.workbook();
        if (!workbook.sheetExists(sheetName)) {
            std::cerr << "Error: Sheet '" << sheetName << 
             "' does not exist in file '" << filePath_cp932 << "'" << std::endl;
            doc.close();
            return;
        }
        OpenXLSX::XLWorksheet sheet = workbook.worksheet(sheetName);

        // Iterate through rows and columns to read data
        // OpenXLSX uses 1-based indexing
        for (auto& row : sheet.rows()) {
            std::vector<std::string> rowData;
            for (auto& cell : row.cells()) {
                // Get cell value and convert to string (which is UTF-8 from the library)
                std::string utf8_value;
                OpenXLSX::XLCellValue cellValue = cell.value();
                switch (cellValue.type()) {
                    case OpenXLSX::XLValueType::Integer:
                        utf8_value = std::to_string(cellValue.get<long long>());
                        break;
                    case OpenXLSX::XLValueType::Float:
                        utf8_value = std::to_string(cellValue.get<double>());
                        break;
                    case OpenXLSX::XLValueType::Boolean:
                        utf8_value = cellValue.get<bool>() ? "TRUE" : "FALSE"; // Or "1" : "0" depending on desired output
                        break;
                    case OpenXLSX::XLValueType::Error:
                        utf8_value = "#ERROR"; // Or get the specific error string
                        break;
                    case OpenXLSX::XLValueType::Empty:
                        utf8_value = "";
                        break;
                    case OpenXLSX::XLValueType::String:
                    default: // Should be XLValueType::String, but default to handle any unhandled types gracefully
                        utf8_value = cellValue.get<std::string>();
                        break;
                }
                // Convert the UTF-8 string to CP932 for use throughout the application
                rowData.push_back(Utf8ToCp932(utf8_value));
            }
            data->push_back(rowData);
        }

        doc.close();
    } catch (const std::exception& e) {
        std::cerr << "Excel library exception: " << e.what() << std::endl;
    }
}


void Excel::readExcelMatomeToVec( std::vector<std::vector<std::string>>* data)
{
    const std::string sheetName = "matome";
    // The file path contains Japanese characters. Since the source file is CP932,
    // this string literal will be correctly encoded as CP932.
    std::string filePath_cp932 = 
                "//192.168.1.247/ã§óL/ãZèpâ€Ã´Ÿ¿ﬁ/ïiéøåüç∏/è¨éÖBééå±ä«óùº∞ƒ.xlsx";

    try {
        // OpenXLSX expects a UTF-8 encoded path. Convert the CP932 path to UTF-8.
        std::string filePath_utf8 = Cp932ToUtf8(filePath_cp932);

        // Open the Excel file
        OpenXLSX::XLDocument doc;
        doc.open(filePath_utf8);

        // Select the specified sheet
        OpenXLSX::XLWorkbook workbook = doc.workbook();
        if (!workbook.sheetExists(sheetName)) {
            std::cerr << "Error: Sheet '" << sheetName << 
             "' does not exist in file '" << filePath_cp932 << "'" << std::endl;
            doc.close();
            return;
        }
        OpenXLSX::XLWorksheet sheet = workbook.worksheet(sheetName);

        // Iterate through rows and columns to read data
        // OpenXLSX uses 1-based indexing
        for (auto& row : sheet.rows()) {
            std::vector<std::string> rowData;
            for (auto& cell : row.cells()) {
                // Get cell value and convert to string (which is UTF-8 from the library)
                std::string utf8_value;
                OpenXLSX::XLCellValue cellValue = cell.value();
                switch (cellValue.type()) {
                    case OpenXLSX::XLValueType::Integer:
                        utf8_value = std::to_string(cellValue.get<long long>());
                        break;
                    case OpenXLSX::XLValueType::Float:
                        utf8_value = std::to_string(cellValue.get<double>());
                        break;
                    case OpenXLSX::XLValueType::Boolean:
                        utf8_value = cellValue.get<bool>() ? "TRUE" : "FALSE"; // Or "1" : "0" depending on desired output
                        break;
                    case OpenXLSX::XLValueType::Error:
                        utf8_value = "#ERROR"; // Or get the specific error string
                        break;
                    case OpenXLSX::XLValueType::Empty:
                        utf8_value = "";
                        break;
                    case OpenXLSX::XLValueType::String:
                    default: // Should be XLValueType::String, but default to handle any unhandled types gracefully
                        utf8_value = cellValue.get<std::string>();
                        break;
                }
                // Convert the UTF-8 string to CP932 for use throughout the application
                rowData.push_back(Utf8ToCp932(utf8_value));
            }
            data->push_back(rowData);
        }

        doc.close();
    } catch (const std::exception& e) {
        std::cerr << "Excel library exception: " << e.what() << std::endl;
    }
}
