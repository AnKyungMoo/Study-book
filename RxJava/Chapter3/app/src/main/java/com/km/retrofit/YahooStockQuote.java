package com.km.retrofit;

import com.google.gson.annotations.SerializedName;

import java.math.BigDecimal;

public class YahooStockQuote {
    private String symbol;

    @SerializedName("Name")
    private String name;

    @SerializedName("LastTradePriceOnly")
    private BigDecimal lastTradePriceOnly;

    @SerializedName("DaysLow")
    private BigDecimal daysLow;

    @SerializedName("DaysHigh")
    private BigDecimal daysHigh;

    @SerializedName("Volume")
    private String volume;

    public BigDecimal getDaysHigh() {
        return daysHigh;
    }

    public BigDecimal getDaysLow() {
        return daysLow;
    }

    public BigDecimal getLastTradePriceOnly() {
        return lastTradePriceOnly;
    }

    public String getName() {
        return name;
    }

    public String getSymbol() {
        return symbol;
    }

    public String getVolume() {
        return volume;
    }
}
