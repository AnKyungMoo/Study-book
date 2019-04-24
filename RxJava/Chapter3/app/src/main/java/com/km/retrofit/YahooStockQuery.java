package com.km.retrofit;

import java.sql.Date;

public class YahooStockQuery {
    private int count;
    private Date create;
    private YahooStockResults result;

    public YahooStockResults getResults() {
        return result;
    }
}
