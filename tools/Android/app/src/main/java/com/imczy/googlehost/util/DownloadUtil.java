package com.imczy.googlehost.util;

import android.content.Context;
import android.os.AsyncTask;

import com.loopj.android.http.AsyncHttpClient;
import com.loopj.android.http.AsyncHttpResponseHandler;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;

import com.imczy.googlehost.Constants;
import cz.msebera.android.httpclient.Header;

/**
 * Created by chenzhiyong on 16/4/17.
 */
public class DownloadUtil {
	private static final String TAG = "DownloadUtil";

	public static void downloadHostFile(final Context context, final DownloadListener downloadListener) {
		AsyncHttpClient mClient = new AsyncHttpClient();
		//TODO umeng配置下载链接
		String url = "https://coding.net/u/scaffrey/p/hosts/git/raw/master/hosts";
		mClient.get(context, url, new AsyncHttpResponseHandler() {
			@Override
			public void onSuccess(int statusCode, final Header[] headers, final byte[] bytes) {
				AsyncTask.execute(new Runnable() {
					@Override
					public void run() {
						OutputStream os = null;
						try {
							long totalLength = 0;
							for (int i = 0; i < headers.length; i++) {
								Header header = headers[i];
								if ("Content-Length".equals(header.getName())) {
									try {
										totalLength = Long.parseLong(header.getValue());
									} catch (Exception e) {
										e.printStackTrace();
									}
								}
							}

							if (bytes == null || bytes.length < totalLength) {
								downloadListener.error();
								return;
							}

							File saveDir = context.getFilesDir();
							if (!saveDir.exists()) {
								saveDir.mkdirs();
							}

							File hostFile = new File(saveDir.getAbsolutePath() + File.separator + Constants.DOWNLOAD_HOST_NAME);
							os = new FileOutputStream(hostFile);
							os.write(bytes);
							downloadListener.success(hostFile);
						} catch (Exception e) {
							e.printStackTrace();
							downloadListener.error();
						} finally {
							if (os != null) {
								try {
									os.close();
								} catch (IOException e) {
									e.printStackTrace();
								}
							}
						}
					}
				});
			}

			@Override
			public void onFailure(int statusCode, Header[] headers, byte[] responseBody, Throwable error) {
				error.printStackTrace();
				downloadListener.error();
			}
		}).setTag(url);
	}


	public interface DownloadListener {
		void success(File file);

		void error();
	}

}
