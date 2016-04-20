package com.imczy.googlehost.util;

import android.content.Context;
import android.os.Environment;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

/**
 * Created by chenzhiyong on 16/4/15.
 */
public class IOUtil {
	public static String getBaseLocalLocation(Context context) {
		boolean isSDCanRead = IOUtil.getExternalStorageState();
		String baseLocation = "";
		if (isSDCanRead) {
			baseLocation = IOUtil.getSDCardPath();
		} else {
			baseLocation = context.getFilesDir().getAbsolutePath();
		}
		return baseLocation;
	}

	public static boolean getExternalStorageState() {
		String state = Environment.getExternalStorageState();
		if (Environment.MEDIA_MOUNTED.equals(state)) {
			return true;
		} else if (Environment.MEDIA_MOUNTED_READ_ONLY.equals(state)) {
			return false;
		} else {
			return false;
		}
	}

	public static String getSDCardPath() {
		return Environment.getExternalStorageDirectory().toString();
	}

	public static boolean copyFile(File srcFile, File destFile) {
		boolean result = false;
		try {
			InputStream in = new FileInputStream(srcFile);
			try {
				result = copyToFile(in, destFile);
			} finally {
				in.close();
			}
		} catch (IOException e) {
			e.printStackTrace();
			result = false;
		}
		return result;
	}

	/**
	 * Copy data from a source stream to destFile. Return true if succeed, return false if failed.
	 */
	public static boolean copyToFile(InputStream inputStream, File destFile) {
		try {
			if (destFile.exists()) {
				destFile.delete();
			}
			FileOutputStream out = new FileOutputStream(destFile);
			try {
				byte[] buffer = new byte[4096];
				int bytesRead;
				while ((bytesRead = inputStream.read(buffer)) >= 0) {
					out.write(buffer, 0, bytesRead);
				}
			} finally {
				out.flush();
				try {
					out.getFD().sync();
				} catch (IOException e) {
				}
				out.close();
			}
			return true;
		} catch (IOException e) {
			e.printStackTrace();
			return false;
		}
	}
}
