package com.km.retrofit;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import io.reactivex.android.schedulers.AndroidSchedulers;
import io.reactivex.schedulers.Schedulers;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // 레트로핏 서비스의 인스턴스를 생성
        YahooService yahooService = new RetrofitYahooServiceFactory().create();

        // 쿼리의 파라미터를 정의
        String query = "select * from yahoo.finance.quote where symbol in ('YHOO', 'APPL', 'GOOG', 'MSFT')";
        String env = "store://datatables.org/alltableswithkeys";

        // 서비스 쿼리를 구독
        yahooService.yqlQuery(query, env)
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(data -> log(
                        data.getQuery().getResults()
                        .getQuote().get(0).getSymbol()
                ));
    }
}
