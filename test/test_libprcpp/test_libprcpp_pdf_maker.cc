#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <future>

#include <json/json.h>
#include <hpdf.h>

#include <libprcpp/types/base_types.hh>
#include <libprcpp/functions/date_and_time_funcs.hh>

using namespace libprcpp;

/////////////////////////////////////////////////////////////////

/**
 * @brief invoice sender data type structure
 */
struct TInvoiceSenderData
{
    std::string name;
    std::string email;
    std::string phone;
    std::string address;
    std::string logo_attachment; // this should be on the top left of pdf invoice, if empty ignore it
    TF64      logo_attachment_scale = 1;
};

/**
 * @brief invoice recipient item type structure
 */
struct TInvoiceRecipientItem
{
    std::string item_name;
    int32_t     quantity;
    TF64      price;
    std::string currency;
};

/**
 * @brief invoice recipient data type structure
 */
struct TInvoiceRecipientData
{
    std::string name;
    std::string email;
    std::string phone;
    std::string address;
};

bool generateBasicInvoice(const std::string &output, const TInvoiceSenderData &invoiceSender, const std::vector<TInvoiceRecipientItem> &invoiceItems, const TInvoiceRecipientData &invoiceRecipient, const std::string &invoiceDate, const std::string &fontName = "Helvetica", const int32_t &fontSize = 10)
{
    HPDF_Doc pdf = HPDF_New(NULL, NULL);
    if (!pdf)
    {
        std::cerr << "Error: Unable to create PDF document" << std::endl;
        return false;
    }

    // enable UTF-8 encoding
    HPDF_UseUTFEncodings(pdf);

    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

    // load font
    HPDF_Font font = HPDF_GetFont(pdf, fontName.c_str(), NULL);
    if (!font)
    {
        std::cerr << "Error: Unable to load font \"" << fontName << "\"" << std::endl;
        HPDF_Free(pdf);
        return false;
    }
    HPDF_Page_SetFontAndSize(page, font, fontSize);

    TF64 margin = 50;
    TF64 y = HPDF_Page_GetHeight(page) - margin;

    // add logo if provided
    if (!invoiceSender.logo_attachment.empty())
    {
        HPDF_Image logo = HPDF_LoadPngImageFromFile(pdf, invoiceSender.logo_attachment.c_str());
        if (!logo)
        {
            std::cerr << "Error: Unable to load logo image" << std::endl;
            HPDF_Free(pdf);
            return false;
        }

        // draw the logo at the top-left corner
        TF64 logoWidth = HPDF_Image_GetWidth(logo);
        TF64 logoHeight = HPDF_Image_GetHeight(logo);
        TF64 scale = invoiceSender.logo_attachment_scale;
        HPDF_Page_DrawImage(page, logo, margin, y - logoHeight * scale, logoWidth * scale, logoHeight * scale);
        y -= logoHeight * scale + 20; // Adjust y position after adding the logo
    }

    // draw sender information
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, margin, y, ("From: " + invoiceSender.name).c_str());
    y -= 20;
    HPDF_Page_TextOut(page, margin, y, ("Email: " + invoiceSender.email).c_str());
    y -= 20;
    HPDF_Page_TextOut(page, margin, y, ("Phone: " + invoiceSender.phone).c_str());
    y -= 20;
    HPDF_Page_TextOut(page, margin, y, ("Address: " + invoiceSender.address).c_str());
    y -= 40;
    HPDF_Page_EndText(page);

    // draw recipient information
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, margin, y, ("To: " + invoiceRecipient.name).c_str());
    y -= 20;
    HPDF_Page_TextOut(page, margin, y, ("Email: " + invoiceRecipient.email).c_str());
    y -= 20;
    HPDF_Page_TextOut(page, margin, y, ("Phone: " + invoiceRecipient.phone).c_str());
    y -= 20;
    HPDF_Page_TextOut(page, margin, y, ("Address: " + invoiceRecipient.address).c_str());
    y -= 40;
    HPDF_Page_EndText(page);

    // draw invoice date
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, margin, y, ("Invoice Date: " + invoiceDate).c_str());
    y -= 40;
    HPDF_Page_EndText(page);

    // draw invoice items table header
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, margin, y, "Item Name");
    HPDF_Page_TextOut(page, margin + 200, y, "Quantity");
    HPDF_Page_TextOut(page, margin + 300, y, "Price");
    HPDF_Page_TextOut(page, margin + 400, y, "Currency");
    y -= 20;
    HPDF_Page_EndText(page);

    // draw invoice items
    for (const auto &item : invoiceItems)
    {
        HPDF_Page_BeginText(page);
        HPDF_Page_TextOut(page, margin, y, item.item_name.c_str());
        HPDF_Page_TextOut(page, margin + 200, y, std::to_string(item.quantity).c_str());
        HPDF_Page_TextOut(page, margin + 300, y, std::to_string(item.price).c_str());
        HPDF_Page_TextOut(page, margin + 400, y, item.currency.c_str());
        y -= 20;
        HPDF_Page_EndText(page);
    }

    // save the document to a file
    HPDF_STATUS status = HPDF_SaveToFile(pdf, output.c_str());
    if (status != HPDF_OK)
    {
        std::cerr << "Error: Unable to save PDF document" << std::endl;
        HPDF_Free(pdf);
        return false;
    }

    HPDF_Free(pdf);
    return true;
}

/////////////////////////////////////////////////////////////////

int main()
{
    const TInvoiceSenderData INVOICE_SENDER{
        "Some Name or Else",
        "some@name.else",
        "0123-4567-8910",
        "Street 1, Province, District, SubDistrict, Country, 123456",
        "../../../../test/test_libprcpp/file_in.png", // Path to the logo image,
        0.05
    };

    const std::string INVOICE_ID = "922D4AE2E597481986431CE562BB57A9";
    const std::string INVOICE_OUTPUT = "_invoice-Foo_Bar-INVOICE_922D4AE2E597481986431CE562BB57A9-YYYY_MM_DD.pdf";
    const std::vector<TInvoiceRecipientItem> INVOICE_ITEMS = {
        {"item 1", 3, 12.345, "USD"},
        {"item 2", 6, 67.891, "USD"},
        {"item 3", 9, 23.456, "USD"},
    };
    const TInvoiceRecipientData INVOICE_RECIPIENT{
        "Foo Bar",
        "foo@bar.baz",
        "63123-4567-8910",
        "Foo Street No. 12, Province, District, SubDistrict, Country, 123456"
    };

    const std::string INVOICE_DATE = dateAndTimeFunctions::UTC::YYYYMMDD::toStringISO8601(dateAndTimeFunctions::localTimeZone());

    auto futureResult = std::async(std::launch::async, generateBasicInvoice, INVOICE_OUTPUT, INVOICE_SENDER, INVOICE_ITEMS, INVOICE_RECIPIENT, INVOICE_DATE, "Helvetica", 10);

    futureResult.wait();

    if (!futureResult.get())
    {
        std::printf("error while generating invoice, try again later\n");
        return -1;
    }

    std::printf("ok, save to \"%s\"\n", INVOICE_OUTPUT.c_str());

    return 0;
}