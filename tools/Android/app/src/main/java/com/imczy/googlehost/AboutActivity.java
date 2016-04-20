package com.imczy.googlehost;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.Html;
import android.text.method.LinkMovementMethod;
import android.widget.TextView;

/**
 * Created by chenzhiyong on 16/4/17.
 */
public class AboutActivity extends AppCompatActivity {


	TextView mAboutTxt, mHostGithubTxt, mAppGithubTxt;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_about);
		mAboutTxt = (TextView) findViewById(R.id.tips);
		mHostGithubTxt = (TextView) findViewById(R.id.host_github_txt);
		mAppGithubTxt = (TextView) findViewById(R.id.app_github_txt);

		String aboutText = getString(R.string.about_detail);
		String hostGithub = getString(R.string.host_github);
		String appGithub = getString(R.string.app_github);

		mAboutTxt.setText(Html.fromHtml(aboutText));
		mHostGithubTxt.setText(Html.fromHtml(hostGithub));
		mAppGithubTxt.setText(Html.fromHtml(appGithub));

		mAboutTxt.setMovementMethod(LinkMovementMethod.getInstance());
		mAppGithubTxt.setMovementMethod(LinkMovementMethod.getInstance());
		mAppGithubTxt.setMovementMethod(LinkMovementMethod.getInstance());

	}


}
